#ifndef STEPPER_CONTROL_H
#define STEPPER_CONTROL_H

#include <AccelStepper.h>

// ULN2003 uses FULL4WIRE
extern AccelStepper magazineStepper;

void StepperTask(void *pvParameters);

#endif