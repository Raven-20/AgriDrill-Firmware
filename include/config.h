#pragma once
#include "pins.h"

// ============================================================
//  AgriDrill Firmware — config.h (FOR 3 BTS7960 SETUP)
// ============================================================


// ── Drive Motion ─────────────────────────────────────────────
#define DRIVE_SPEED_FWD         180
#define DRIVE_SPEED_TURN        150
#define MOTOR_RAMP_MS           200


// ── Linear Actuator (Drilling Mechanism) ─────────────────────
#define ACTUATOR_EXTEND_MS      2500
#define ACTUATOR_RETRACT_MS     2500
#define ACTUATOR_DWELL_MS       500


// ── Stepper / Tray Cycle ─────────────────────────────────────
#define STEPPER_STEPS_PER_REV   200
#define STEPPER_RPM             60
#define TRAY_TOTAL_SLOTS        5
#define TRAY_STEPS_PER_SLOT     40


// ── Ultrasonic Sensor ────────────────────────────────────────
#define ULTRASONIC_TIMEOUT_US   30000
#define OBSTACLE_STOP_CM        20


// ── Servo Settings ───────────────────────────────────────────
#define SERVO_DEFAULT_ANGLE     90
#define SERVO_LEFT_ANGLE        45
#define SERVO_RIGHT_ANGLE       135


// ── Serial Debug ─────────────────────────────────────────────
#define SERIAL_DEBUG_BAUD       115200