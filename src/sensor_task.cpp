#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"     
#include "config.h" 
#include "ultrasonic.h"   
#include "pins.h" 
#include <ESP32Servo.h>
#include "system_state.h"

// Then define servo object
Servo scanServo;

Ultrasonic ultrasonic(ULTRASONIC_TRIG_PIN, ULTRASONIC_ECHO_PIN);

void SensorTaskFunction(void *pvParameters)
{
    ultrasonic.begin();
    scanServo.attach(SERVO_PIN);

    int leftAngle = 30;
    int centerAngle = 90;
    int rightAngle = 150;

    while (true)
    {
        if (currentState == SCAN)
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

            // STORE values (no Serial spam)
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}