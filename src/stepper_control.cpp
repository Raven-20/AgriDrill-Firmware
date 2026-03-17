#include <Arduino.h>
#include <Stepper.h>
#include "stepper_control.h"
#include "config.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "system_state.h"

// ✅ ULN2003 uses 4 pins
AccelStepper magazineStepper(
    AccelStepper::FULL4WIRE,
    STEPPER_IN1,
    STEPPER_IN3,
    STEPPER_IN2,
    STEPPER_IN4
);

void StepperTask(void *pvParameters)
{
    magazineStepper.setMaxSpeed(500);
    magazineStepper.setSpeed(200);

    while (true)
    {
        magazineStepper.runSpeed();  // 🔥 required
    }
}