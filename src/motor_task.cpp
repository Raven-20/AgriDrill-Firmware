#include <Arduino.h>
#include "config.h"
#include "motor_task.h"

int motorSpeed = 0;
String motorDirection = "STOP";

void MotorControlTask(void *pvParameters)
{
    while (true)
    {
        if (Serial.available())
        {
            char cmd = Serial.read();

            switch(cmd)
            {
                case 'f':
                    motorDirection = "FORWARD";
                    ledcWrite(LEFT_RPWM_CHANNEL, motorSpeed);
                    ledcWrite(LEFT_LPWM_CHANNEL, 0);
                    ledcWrite(RIGHT_RPWM_CHANNEL, motorSpeed);
                    ledcWrite(RIGHT_LPWM_CHANNEL, 0);
                    break;

                case 'r':
                    motorDirection = "REVERSE";
                    ledcWrite(LEFT_RPWM_CHANNEL, 0);
                    ledcWrite(LEFT_LPWM_CHANNEL, motorSpeed);
                    ledcWrite(RIGHT_RPWM_CHANNEL, 0);
                    ledcWrite(RIGHT_LPWM_CHANNEL, motorSpeed);
                    break;

                case 's':
                    motorDirection = "STOP";
                    motorSpeed = 0;

                    ledcWrite(LEFT_RPWM_CHANNEL, 0);
                    ledcWrite(LEFT_LPWM_CHANNEL, 0);
                    ledcWrite(RIGHT_RPWM_CHANNEL, 0);
                    ledcWrite(RIGHT_LPWM_CHANNEL, 0);
                    break;

                case '1':
                    motorSpeed = 80;
                    break;

                case '2':
                    motorSpeed = 160;
                    break;

                case '3':
                    motorSpeed = 255;
                    break;
            }

            Serial.println("----- MOTOR STATUS -----");
            Serial.print("Direction: ");
            Serial.println(motorDirection);

            Serial.print("Speed PWM: ");
            Serial.println(motorSpeed);
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}