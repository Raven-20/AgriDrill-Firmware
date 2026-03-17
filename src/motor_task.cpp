#include <Arduino.h>
#include "config.h"
#include "motor_task.h"
#include "system_state.h"

void MotorControlTask(void *pvParameters)
{
    while (true)
    {
        switch (currentState)
        {
        case MOVE_FORWARD:
            ledcWrite(LEFT_RPWM_CHANNEL, 150);
            ledcWrite(LEFT_LPWM_CHANNEL, 0);
            ledcWrite(RIGHT_RPWM_CHANNEL, 150);
            ledcWrite(RIGHT_LPWM_CHANNEL, 0);
            break;

        case STOP:
            ledcWrite(LEFT_RPWM_CHANNEL, 0);
            ledcWrite(LEFT_LPWM_CHANNEL, 0);
            ledcWrite(RIGHT_RPWM_CHANNEL, 0);
            ledcWrite(RIGHT_LPWM_CHANNEL, 0);
            break;

        default:
            break;
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}