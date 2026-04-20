#include <Arduino.h>
#include "pins.h"
#include "config.h"

// ================= PWM SETTINGS =================
#define ACT_PWM_FREQ     20000
#define ACT_PWM_RES      8

#define ACT_RPWM_CH      0
#define ACT_LPWM_CH      1

// ================= FUNCTIONS =================
void actuatorInit()
{
    pinMode(PIN_ACT_RPWM, OUTPUT);
    pinMode(PIN_ACT_LPWM, OUTPUT);
    pinMode(PIN_ACT_REN, OUTPUT);
    pinMode(PIN_ACT_LEN, OUTPUT);

    digitalWrite(PIN_ACT_REN, HIGH);
    digitalWrite(PIN_ACT_LEN, HIGH);

    ledcSetup(ACT_RPWM_CH, ACT_PWM_FREQ, ACT_PWM_RES);
    ledcSetup(ACT_LPWM_CH, ACT_PWM_FREQ, ACT_PWM_RES);

    ledcAttachPin(PIN_ACT_RPWM, ACT_RPWM_CH);
    ledcAttachPin(PIN_ACT_LPWM, ACT_LPWM_CH);

    // Stop actuator initially
    ledcWrite(ACT_RPWM_CH, 0);
    ledcWrite(ACT_LPWM_CH, 0);
}

void actuatorStop()
{
    ledcWrite(ACT_RPWM_CH, 0);
    ledcWrite(ACT_LPWM_CH, 0);
}

void actuatorExtend(uint8_t speed)
{
    ledcWrite(ACT_RPWM_CH, speed);
    ledcWrite(ACT_LPWM_CH, 0);
}

void actuatorRetract(uint8_t speed)
{
    ledcWrite(ACT_RPWM_CH, 0);
    ledcWrite(ACT_LPWM_CH, speed);
}

// ================= TASK =================
void actuatorTask(void *pvParameters)
{
    actuatorInit();

    while (true)
    {
        // FULL EXTEND TEST
        actuatorExtend(200);
        vTaskDelay(pdMS_TO_TICKS(15000));

        // STOP
        actuatorStop();
        vTaskDelay(pdMS_TO_TICKS(2000));

        // FULL RETRACT TEST
        actuatorRetract(200);
        vTaskDelay(pdMS_TO_TICKS(15000));

        // STOP
        actuatorStop();
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}