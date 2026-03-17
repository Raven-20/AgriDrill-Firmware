#include <Arduino.h>
#include "config.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "motor_task.h"
#include "stepper_control.h"
#include "ultrasonic.h"
#include "pins.h"
#include <ESP32Servo.h>
#include "encoder.h"
#include "system_state.h"

// ===== FUNCTION PROTOTYPES =====
void SensorTaskFunction(void *pvParameters);
void ActuatorTaskFunction(void *pvParameters);
void CommunicationTaskFunction(void *pvParameters);
void SystemMonitorTaskFunction(void *pvParameters);
void EncoderTask(void *pvParameters);
void SystemControlTask(void *pvParameters);

// ===== TASK HANDLES =====
TaskHandle_t MotorTaskHandle;
TaskHandle_t SensorTaskHandle;
TaskHandle_t ActuatorTaskHandle;
TaskHandle_t StepperTaskHandle;
TaskHandle_t CommunicationTaskHandle;
TaskHandle_t SystemMonitorTaskHandle;
TaskHandle_t EncoderTaskHandle;
TaskHandle_t SystemControlTaskHandle;


// ===== ACTUATOR STATES =====
enum ActuatorState
{
    ACT_STATE_IDLE,
    ACT_STATE_EXTENDING,
    ACT_STATE_RETRACTING
};

// ================= ACTUATOR TASK =================
void ActuatorTaskFunction(void *pvParameters)
{
    pinMode(ACT_EN, OUTPUT);
    pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

    digitalWrite(ACT_EN, HIGH);
    ActuatorState state = ACT_STATE_IDLE;

    while (true)
    {
        switch (state)
        {
        case ACT_STATE_IDLE:
            vTaskDelay(pdMS_TO_TICKS(100));
            break;

        case ACT_STATE_EXTENDING:
            ledcWrite(ACT_RPWM_CHANNEL, 180);
            ledcWrite(ACT_LPWM_CHANNEL, 0);
            vTaskDelay(pdMS_TO_TICKS(3000));

            ledcWrite(ACT_RPWM_CHANNEL, 0);
            state = ACT_STATE_RETRACTING;
            break;

        case ACT_STATE_RETRACTING:
            ledcWrite(ACT_LPWM_CHANNEL, 180);
            vTaskDelay(pdMS_TO_TICKS(3000));

            if (digitalRead(LIMIT_SWITCH_PIN) == LOW)
            {
                ledcWrite(ACT_LPWM_CHANNEL, 0);
                state = ACT_STATE_IDLE;
            }
            break;
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

// ================= ENCODER TASK =================
void EncoderTask(void *pvParameters)
{
    encoder_init();
    pinMode(ENCODER_A, INPUT_PULLUP);
    pinMode(ENCODER_B, INPUT_PULLUP);

    long lastCount = -1;

    while (true)
    {
        long count = encoder_getCount();

        if (count != lastCount)
        {
            Serial.print("[ENCODER] Count: ");
            Serial.println(count);
            lastCount = count;
        }

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

// ================= SYSTEM CONTROL TASK =================
void SystemControlTask(void *pvParameters)
{
    int cycle = 1;

    while (true)
    {
        switch (currentState)
        {
        case INIT:
            Serial.println("\n==============================");
            Serial.println(" AGRIDRILL SYSTEM START ");
            Serial.println("==============================\n");
            currentState = SCAN;
            break;

        case SCAN:
            Serial.println("[SENSOR] Scanning...");
            currentState = MOVE_FORWARD;
            break;

        case MOVE_FORWARD:
            Serial.println("[MOTOR] Moving Forward...");
            currentState = STOP;
            break;

        case STOP:
            Serial.println("[MOTOR] Stop");
            currentState = INDEX_TRAY;
            break;

        case INDEX_TRAY:
            Serial.print("[STEPPER] Tray Position: ");
            Serial.println(cycle);
            currentState = DRILL;
            break;

        case DRILL:
            Serial.println("[ACTUATOR] Drilling...");
            currentState = RETRACT;
            break;

        case RETRACT:
            Serial.println("[ACTUATOR] Retracting...");
            currentState = DROP_SEED;
            break;

        case DROP_SEED:
            Serial.println("[SERVO] Seed Dropped");
            currentState = NEXT_POSITION;
            break;


        case NEXT_POSITION:
            Serial.println("\n------------------------------");
            Serial.print("Cycle #");
            Serial.println(cycle);
            Serial.println("Moving to next position...");
            Serial.println("------------------------------\n");

            cycle++;
            currentState = SCAN;
            break;
        }

        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

// ================= OTHER TASKS =================
void CommunicationTaskFunction(void *pvParameters)
{
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void SystemMonitorTaskFunction(void *pvParameters)
{
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(4000));
    }
}

// ================= SETUP =================
void setup()
{
    Serial.begin(115200);
    Serial.println("\nSystem Initializing...");

    // ===== MOTOR PWM SETUP =====
    ledcSetup(LEFT_RPWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(MOTOR_LEFT_RPWM, LEFT_RPWM_CHANNEL);

    ledcSetup(LEFT_LPWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(MOTOR_LEFT_LPWM, LEFT_LPWM_CHANNEL);

    ledcSetup(RIGHT_RPWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(MOTOR_RIGHT_RPWM, RIGHT_RPWM_CHANNEL);

    ledcSetup(RIGHT_LPWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(MOTOR_RIGHT_LPWM, RIGHT_LPWM_CHANNEL);

    // ===== ACTUATOR PWM SETUP =====
    ledcSetup(ACT_RPWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(ACTUATOR_RPWM, ACT_RPWM_CHANNEL);

    ledcSetup(ACT_LPWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(ACTUATOR_LPWM, ACT_LPWM_CHANNEL);

    // ===== CREATE TASKS =====
    xTaskCreatePinnedToCore(SystemControlTask, "SystemControl", 4096, NULL, 2, &SystemControlTaskHandle, 1);

    xTaskCreatePinnedToCore(MotorControlTask, "MotorControl", 4096, NULL, 2, &MotorTaskHandle, 1);
    xTaskCreatePinnedToCore(SensorTaskFunction, "SensorTask", 2048, NULL, 2, &SensorTaskHandle, 1);
    xTaskCreatePinnedToCore(ActuatorTaskFunction, "ActuatorTask", 4096, NULL, 1, &ActuatorTaskHandle, 1);
    xTaskCreatePinnedToCore(StepperTask, "StepperTask", 4096, NULL, 1, &StepperTaskHandle, 1);

    xTaskCreatePinnedToCore(CommunicationTaskFunction, "CommunicationTask", 4096, NULL, 1, &CommunicationTaskHandle, 0);
    xTaskCreatePinnedToCore(SystemMonitorTaskFunction, "SystemMonitor", 4096, NULL, 1, &SystemMonitorTaskHandle, 0);
    xTaskCreatePinnedToCore(EncoderTask, "EncoderTask", 2048, NULL, 1, &EncoderTaskHandle, 0);

    Serial.println("System Initialization Complete.\n");
}

void loop()
{
}