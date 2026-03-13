#include "encoder.h"
#include "../../include/pins.h"

volatile long encoderCount = 0;
volatile int lastEncoded = 0;

void IRAM_ATTR handleEncoder()
{
    int MSB = digitalRead(ENCODER_A);
    int LSB = digitalRead(ENCODER_B);

    int encoded = (MSB << 1) | LSB;
    int sum = (lastEncoded << 2) | encoded;

    if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
        encoderCount++;

    if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
        encoderCount--;

    lastEncoded = encoded;
}

void encoder_init()
{
    pinMode(ENCODER_A, INPUT_PULLUP);
    pinMode(ENCODER_B, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(ENCODER_A), handleEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_B), handleEncoder, CHANGE);
}

long encoder_getCount()
{
    return encoderCount;
}