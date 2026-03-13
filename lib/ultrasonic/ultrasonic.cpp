#include "ultrasonic.h"

Ultrasonic::Ultrasonic(int trig, int echo)
{
    trigPin = trig;
    echoPin = echo;
}

void Ultrasonic::begin()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

long Ultrasonic::read()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);

    long distance = duration * 0.034 / 2;

    return distance;
}