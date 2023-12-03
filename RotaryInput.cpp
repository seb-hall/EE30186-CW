//  RotaryInput.cpp
//  EE30186 CW
//
//  This file implements a simple interface for reading a rotary encoder

#include "RotaryInput.h"

//  encoder interrupts
static InterruptIn interruptA(pinA);
static InterruptIn interruptB(pinB);

//  states for pins - high = true, low = false
static bool isPinAHigh;
static bool isPinBHigh;

//  timers that get reset when the pins change after debounce threshold
static Timer timeSincePinAChange;
static Timer timeSincePinBChange;

//  private encoder position
static int encoderPosition;

//  callback functions for encoder logic
static void PinARise();
static void PinAFall();
static void PinBRise();
static void PinBFall();

//  init function to set up interrupts
void RotaryInput_Init() {
    // start timers
    timeSincePinAChange.start();
    timeSincePinBChange.start();

    // set interrupt callbacks
    interruptA.rise(PinARise);
    interruptA.fall(PinAFall);
    interruptB.rise(PinBRise);
    interruptB.fall(PinBFall);

}

//  get position as a number of 'notches'
//  positive is clockwise and negative is 
//  counter-clockwise
int RotaryInput_GetPosition() {
    return encoderPosition;
}

//  callback triggered by PA_1 going high
void PinARise() {

    // check if a few ms have elapsed since the last change
    if (std::chrono::duration_cast<std::chrono::milliseconds>
        (timeSincePinAChange.elapsed_time()) > debounceThreshold) {

        // it has been so check if PA1_state was previously LOW
        if (!isPinAHigh) {
            // it was so change the state and reset the timer
            isPinAHigh = true;
            timeSincePinAChange.reset();

            //  if Pin B is also high then it went high before this
            //  and has an advanced phase
            if (isPinBHigh) {
                //  increment the position by 1
                encoderPosition += 1;
            //  otherwise it has a retarded phase
            } else {
                //  decrement the position by 1
                encoderPosition -= 1;                
            }
        }
    }
}

void PinAFall() {

    // check if a few ms have elapsed since the last change
    if (std::chrono::duration_cast<std::chrono::milliseconds>
        (timeSincePinAChange.elapsed_time()) > debounceThreshold) {

        // it has been so check if PA1_state was previously HIGH    
        if (isPinAHigh) {
            // it was so change the state and reset the timer
            isPinAHigh = false;
            timeSincePinAChange.reset();
        }
    }
}

//  callback triggered by PA_4 going high
void PinBRise() {

    // check if a few ms have elapsed since the last change
    if (std::chrono::duration_cast<std::chrono::milliseconds>
        (timeSincePinBChange.elapsed_time()) > debounceThreshold) {

        // it has been so check if PA4_state was previously LOW
        if (!isPinBHigh) {
            // it was so change the state and reset the timer
            isPinBHigh = true;
            timeSincePinBChange.reset();

        }
    }
}

//  callback triggered by PA_4 going low
void PinBFall() {

    // check if a few ms have elapsed since the last change
    if (std::chrono::duration_cast<std::chrono::milliseconds>
        (timeSincePinBChange.elapsed_time()) > debounceThreshold) {

        // it has been so check if PA4_state was previously HIGH
        if (isPinBHigh) {
            // it was so change the state and reset the timer
            isPinBHigh = false;
            timeSincePinBChange.reset();
        }
    }
}
