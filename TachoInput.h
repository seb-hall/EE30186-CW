//  TachoInput.h
//  EE30186 CW
//
//  This file contains a simple interface for reading a rotary encoder

#include "mbed.h"

//  encoder pins
const PinName tachoPin = PA_0;
const int pulsesPerRevolution = 2;

//  init function to set up interrupts
void TachoInput_Init();

//  get position as floating point measure
//  in RPM
int TachoInput_GetRpm();

