//  TachoInput.cpp
//  EE30186 CW
//
//  This file implements a simple interface for reading the speed of a DC fan

#include "TachoInput.h"
#include <cstdio>

static InterruptIn tachoInterrupt(tachoPin);
static Timer tachoTimer;
static Timer lastPulseTimer;

static void TachoRise();

volatile unsigned long pulseCount = 0;

//  init function to set up interrupts
void TachoInput_Init() {

    // set interrupt callbacks
    tachoInterrupt.rise(TachoRise);

    // start tacho timer
    tachoTimer.start();
    lastPulseTimer.start();
}


int TachoInput_GetRpm() {

    long timeElapsed = tachoTimer.elapsed_time().count(); // Time in microseconds
    tachoTimer.reset();

    tachoInterrupt.disable_irq();
    unsigned long count = pulseCount;
    pulseCount = 0;
    tachoInterrupt.enable_irq();

    // Calculate RPM (adjust the formula based on your fan's specification)
    unsigned int rpm = (count * 60 * 1000000) / (timeElapsed * pulsesPerRevolution);
    return rpm;
}

//  callback triggered by tacho going high
void TachoRise() { 

    if (lastPulseTimer.elapsed_time().count() > 100) {
        lastPulseTimer.reset();
        pulseCount++;

    }
}
