#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("AgriDrill ESP32 Boot Successful");
}

void loop() {
    Serial.println("System Running...");
    delay(1000);
}