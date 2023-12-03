//  TachoInput.cpp
//  EE30186 CW
//
//  This file implements a simple interface for reading the speed of a DC fan

#include "TachoInput.h"
#include <cstdio>

static InterruptIn tachoInterrupt(tachoPin);
static Timer timeSinceLastTacho;

static void TachoRise();

static float lastFrequency = 0.0f;

//  init function to set up interrupts
void TachoInput_Init() {
    // start timers
    timeSinceLastTacho.start();

    // set interrupt callbacks
    tachoInterrupt.rise(TachoRise);

}

//  callback triggered by tacho going high
void TachoRise() { 
    long long timeSinceLastHigh = timeSinceLastTacho.elapsed_time().count();
    timeSinceLastTacho.reset();

    lastFrequency = 1.0f/((float) timeSinceLastHigh / 1000000.0f);
    //lastFrequency = 1.0f;
}

float TachoInput_GetSpeed() {
    return lastFrequency;
}
