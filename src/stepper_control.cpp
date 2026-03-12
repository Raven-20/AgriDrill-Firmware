#include <Arduino.h>
#include <Stepper.h>
#include "stepper_control.h"
#include "config.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// ===== STEPPER OBJECT =====
Stepper magazineStepper(
    STEPS_PER_REV,
    STEPPER_IN1,
    STEPPER_IN3,
    STEPPER_IN2,
    STEPPER_IN4
);


// ===== STEPPER TASK =====
void StepperTask(void *pvParameters)
{
    magazineStepper.setSpeed(10);   // RPM

    int cycleCount = 0;

    while (1)
    {
        if (cycleCount < 10)
        {
            Serial.print("Stepper Index Cycle: ");
            Serial.println(cycleCount + 1);

            Serial.println("Moving to next tray position...");

            magazineStepper.step(STEPS_PER_CELL);

            Serial.println("Position reached.");
            Serial.println("----------------------");

            cycleCount++;

            vTaskDelay(pdMS_TO_TICKS(2000));
        }
        else
        {
            Serial.println("10 index cycles completed.");
            vTaskDelay(pdMS_TO_TICKS(5000));
        }
    }
}