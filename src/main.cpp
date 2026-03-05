#include <Arduino.h>
#include "config.h"

// ===== TASK HANDLES =====
TaskHandle_t MotorTask;
TaskHandle_t SensorTask;
TaskHandle_t ActuatorTask;
TaskHandle_t CommunicationTask;
TaskHandle_t SystemMonitorTask;


// ================= MOTOR TASK =================
void MotorControlTask(void *pvParameters)
{
    while (true)
    {
        Serial.println("Motor Control Task Running");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


// ================= SENSOR TASK =================
void SensorTaskFunction(void *pvParameters)
{
    while (true)
    {
        Serial.println("Sensor Task Running");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


// ================= ACTUATOR TASK =================
void ActuatorTaskFunction(void *pvParameters)
{
    while (true)
    {
        Serial.println("Actuator Task Running");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


// ================= COMMUNICATION TASK =================
void CommunicationTaskFunction(void *pvParameters)
{
    while (true)
    {
        Serial.println("Communication Task Running");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


// ================= SYSTEM MONITOR TASK =================
void SystemMonitorTaskFunction(void *pvParameters)
{
    while (true)
    {
        Serial.println("System Monitor Running");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}


void setup()
{
    Serial.begin(115200);

    // ===== CREATE TASKS =====

    xTaskCreatePinnedToCore(
        MotorControlTask,
        "MotorControl",
        4096,
        NULL,
        2,
        &MotorTask,
        1);

    xTaskCreatePinnedToCore(
        SensorTaskFunction,
        "SensorTask",
        4096,
        NULL,
        2,
        &SensorTask,
        1);

    xTaskCreatePinnedToCore(
        ActuatorTaskFunction,
        "ActuatorTask",
        4096,
        NULL,
        2,
        &ActuatorTask,
        1);

    xTaskCreatePinnedToCore(
        CommunicationTaskFunction,
        "CommunicationTask",
        4096,
        NULL,
        1,
        &CommunicationTask,
        0);

    xTaskCreatePinnedToCore(
        SystemMonitorTaskFunction,
        "SystemMonitor",
        4096,
        NULL,
        1,
        &SystemMonitorTask,
        0);
}

void loop()
{
}