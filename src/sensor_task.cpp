#include <Arduino.h>
#include "config.h"
#include "pins.h"
#include "ultrasonic.h"
#include <ESP32Servo.h>

// ================= LIMIT SWITCH VARIABLES =================
volatile bool limitSwitchTriggered = false;
volatile unsigned long lastInterruptTime = 0;

// ================= INTERRUPT SERVICE ROUTINE =================
void IRAM_ATTR limitSwitchISR()
{
    unsigned long currentTime = millis();

    if ((currentTime - lastInterruptTime) >= LIMIT_SWITCH_DEBOUNCE_MS)
    {
        limitSwitchTriggered = true;
        lastInterruptTime = currentTime;
    }
}

Ultrasonic ultrasonic(5, 18);
Servo scanServo;

int leftAngle = 45;
int centerAngle = 90;
int rightAngle = 135;

// ================= SENSOR TASK =================
void SensorTaskFunction(void *pvParameters)
{
    // ----- LIMIT SWITCH SETUP -----
    pinMode(16, INPUT_PULLUP);

    attachInterrupt(
        digitalPinToInterrupt(16),
        limitSwitchISR,
        FALLING); // switch pressed

    // ----- ULTRASONIC + SERVO SETUP -----
    ultrasonic.begin();
    scanServo.attach(19);

    while (true)
    {
        // -------- TEMPORARY TEST --------
        limitSwitchISR();   // simulate switch press

        // ================= LIMIT SWITCH CHECK =================
        if (limitSwitchTriggered)
        {
            Serial.println("Limit switch triggered!");
            limitSwitchTriggered = false;
        }

        // ================= ULTRASONIC SCAN =================
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