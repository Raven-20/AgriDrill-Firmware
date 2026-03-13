#pragma once
#include <Arduino.h>

class Ultrasonic
{
private:
    int trigPin;
    int echoPin;

public:
    Ultrasonic(int trig, int echo);

    void begin();

    long read();
};