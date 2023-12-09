#ifndef BUTTONINPUT_H
#define BUTTONINPUT_H

#include "mbed.h"

constexpr std::chrono::milliseconds buttonDebounceTime = 100ms;

void ButtonInput_Init();


//  return if button has been pressed since the last call
//  resets to false after the function is called
bool HasButtonBeenPressed();


#endif // BUTTONINPUT_H