#ifndef CONFIG_H
#define CONFIG_H

// ==================================================
// LEFT MOTOR (BTS7960)
// ==================================================
#define MOTOR_LEFT_RPWM 25
#define MOTOR_LEFT_LPWM 13

// ==================================================
// RIGHT MOTOR (BTS7960)
// ==================================================
#define MOTOR_RIGHT_RPWM 26
#define MOTOR_RIGHT_LPWM 12


// ==================================================
// ULTRASONIC SENSOR
// ==================================================
#define ULTRASONIC_TRIG 33
#define ULTRASONIC_ECHO 32


// ==================================================
// LINEAR ACTUATOR (BTS7960)
// ==================================================
#define ACTUATOR_RPWM 27
#define ACTUATOR_LPWM 14
#define ACT_EN 23
#define LIMIT_SWITCH_PIN 34


// ==================================================
// STEPPER MOTOR (ULN2003)
// ==================================================
#define STEPPER_IN1 18
#define STEPPER_IN2 19
#define STEPPER_IN3 21
#define STEPPER_IN4 22


// ==================================================
// PWM SETTINGS
// ==================================================
#define PWM_FREQ 20000
#define PWM_RESOLUTION 8


// ==================================================
// PWM CHANNELS
// ==================================================
#define LEFT_RPWM_CHANNEL 0
#define LEFT_LPWM_CHANNEL 1
#define RIGHT_RPWM_CHANNEL 2
#define RIGHT_LPWM_CHANNEL 3
#define ACT_RPWM_CHANNEL 4
#define ACT_LPWM_CHANNEL 5


#endif