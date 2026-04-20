#pragma once

// ============================================================
//  AgriDrill Firmware — pins.h (FINAL CLEAN VERSION)
//  ESP32 Devkit V1 + 3x BTS7960 + A4988 + Sensors
// ============================================================


// ============================================================
// BTS7960 #1 (FRONT WHEELS MOTOR DRIVER)
// ============================================================
#define PIN_FRONT_RPWM      25
#define PIN_FRONT_LPWM      26
//#define PIN_FRONT_REN       27
//#define PIN_FRONT_LEN       14


// ============================================================
// BTS7960 #2 (BACK WHEELS MOTOR DRIVER)
// ============================================================
#define PIN_BACK_RPWM       27   //33
#define PIN_BACK_LPWM       14   //32
//#define PIN_BACK_REN        23
//#define PIN_BACK_LEN        22


// ============================================================
// BTS7960 #3 (LINEAR ACTUATOR DRIVER)
// ============================================================
#define PIN_ACT_RPWM        18
#define PIN_ACT_LPWM        19
#define PIN_ACT_REN         32  //5
#define PIN_ACT_LEN         33  //17


// ============================================================
// A4988 / DRV8825 STEPPER MOTOR DRIVER (NEMA17)
// ============================================================
#define PIN_STEP            12
#define PIN_DIR             13
#define PIN_STEP_EN         16      // optional (LOW = enabled)


// ============================================================
// ULTRASONIC SENSOR (HC-SR04)
// ============================================================
#define PIN_ULTRASONIC_TRIG 4
#define PIN_ULTRASONIC_ECHO 15


// ============================================================
// SERVO MOTOR
// ============================================================
#define PIN_SERVO           21


// ============================================================
// BUZZER
// ============================================================
#define PIN_BUZZER          2


// ============================================================
// OPTIONAL SYSTEM BUTTON
// ============================================================
#define PIN_START_BUTTON    34      // input-only pin OK for button