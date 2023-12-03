//  RotaryInput.h
//  EE30186 CW
//
//  This file contains a simple interface for reading a rotary encoder

#include "mbed.h"

//  debounce timeout threshold in ms
constexpr std::chrono::milliseconds debounceThreshold = 10ms;

//  encoder pins
const PinName pinA = PA_1;
const PinName pinB = PA_4;

//  init function to set up interrupts
void RotaryInput_Init();

//  get position as a number of 'notches'
//  positive is clockwise and negative is 
//  counter-clockwise
int RotaryInput_GetPosition();

