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


// ===== FUNCTION PROTOTYPES =====
void SensorTaskFunction(void *pvParameters);
void ActuatorTaskFunction(void *pvParameters);
void CommunicationTaskFunction(void *pvParameters);
void SystemMonitorTaskFunction(void *pvParameters);

// ===== TASK HANDLES =====
TaskHandle_t MotorTaskHandle;
TaskHandle_t SensorTaskHandle;
TaskHandle_t ActuatorTaskHandle;
TaskHandle_t StepperTaskHandle;
TaskHandle_t CommunicationTaskHandle;
TaskHandle_t SystemMonitorTaskHandle;
TaskHandle_t EncoderTaskHandle;


Ultrasonic ultrasonic(5, 18);
Servo scanServo;

int leftAngle = 45;
int centerAngle = 90;
int rightAngle = 135;

// ================= SENSOR TASK =================
void SensorTaskFunction(void *pvParameters)
{
    ultrasonic.begin();
    scanServo.attach(19);

    while (true)
    {
        scanServo.write(leftAngle);
        vTaskDelay(pdMS_TO_TICKS(200));
        long leftDist = ultrasonic.read();

        scanServo.write(centerAngle);
        vTaskDelay(pdMS_TO_TICKS(200));
        long centerDist = ultrasonic.read();

        scanServo.write(rightAngle);
        vTaskDelay(pdMS_TO_TICKS(200));
        long rightDist = ultrasonic.read();

        Serial.print("Left: ");
        Serial.print(leftDist);
        Serial.print(" cm | Center: ");
        Serial.print(centerDist);
        Serial.print(" cm | Right: ");
        Serial.print(rightDist);
        Serial.println(" cm");
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}


// ================= ACTUATOR TASK =================
void ActuatorTaskFunction(void *pvParameters)
{
    Serial.println("Actuator Task Started");

    pinMode(ACT_EN, OUTPUT);
    pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

    digitalWrite(ACT_EN, HIGH);

    while (true)
    {
        Serial.println("Extending actuator...");
        ledcWrite(ACT_RPWM_CHANNEL, 180);
        ledcWrite(ACT_LPWM_CHANNEL, 0);

        vTaskDelay(pdMS_TO_TICKS(3000));

        Serial.println("Stopping actuator");
        ledcWrite(ACT_RPWM_CHANNEL, 0);
        ledcWrite(ACT_LPWM_CHANNEL, 0);

        vTaskDelay(pdMS_TO_TICKS(1000));

        Serial.println("Retracting actuator...");
        ledcWrite(ACT_RPWM_CHANNEL, 0);
        ledcWrite(ACT_LPWM_CHANNEL, 180);

        vTaskDelay(pdMS_TO_TICKS(3000));

        if (digitalRead(LIMIT_SWITCH_PIN) == LOW)
        {
            Serial.println("Limit switch reached. Full retraction confirmed.");
            ledcWrite(ACT_LPWM_CHANNEL, 0);
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}


// ================= COMMUNICATION TASK =================
void CommunicationTaskFunction(void *pvParameters)
{
    while (true)
    {
        Serial.println("[Core0] Communication Task Running");
        vTaskDelay(pdMS_TO_TICKS(2500));
    }
}


// ================= SYSTEM MONITOR TASK =================
void SystemMonitorTaskFunction(void *pvParameters)
{
    while (true)
    {
        Serial.println("[Core0] System Monitor Running");
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

// ================= SYSTEM MONITOR TASK =================
void EncoderTask(void *pvParameters)
{
    encoder_init();

    TickType_t lastWakeTime = xTaskGetTickCount();

    while(true)
    {
        long count = encoder_getCount();

        Serial.print("Encoder Count: ");
        Serial.println(count);

        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(50));
    }
}


void setup()
{
    Serial.begin(115200);

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

    xTaskCreatePinnedToCore(
        MotorControlTask,
        "MotorControl",
        4096,
        NULL,
        2,
        &MotorTaskHandle,
        1);

    xTaskCreatePinnedToCore(
        SensorTaskFunction,
        "SensorTask",
        2048,
        NULL,
        2,
        &SensorTaskHandle,
        1);

    xTaskCreatePinnedToCore(
        ActuatorTaskFunction,
        "ActuatorTask",
        2048,
        NULL,
        1,
        &ActuatorTaskHandle,
        1);

    xTaskCreatePinnedToCore(
        StepperTask,
        "Stepper Task",
        4096,
        NULL,
        1,
        &StepperTaskHandle,
        1);   
        
    xTaskCreatePinnedToCore(
        CommunicationTaskFunction,
        "CommunicationTask",
        4096,
        NULL,
        1,
        &CommunicationTaskHandle,
        0);

    xTaskCreatePinnedToCore(
        SystemMonitorTaskFunction,
        "SystemMonitor",
        4096,
        NULL,
        1,
        &SystemMonitorTaskHandle,
        0);

    xTaskCreatePinnedToCore(
        EncoderTask,
        "EncoderTask",
        2048,
        NULL,
        1,
        &EncoderTaskHandle,
        0);    
}

void loop()
{
}