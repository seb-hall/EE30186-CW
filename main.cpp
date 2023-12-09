//  main.cpp
//  EE30186 CW
//
//  This file is the program entry point and controls the overall
//  program control flow


#include "mbed.h"
#include "RotaryInput.h"
#include "FourteenSegmentDisplay.h"
#include "TempSensor.h"
#include "ButtonInput.h"
#include "TachoInput.h"
#include <cstdio>

#include <vector>

enum RunMode {
    PC_CONTROL_DISPLAY_PC,
    PC_CONTROL_DISPLAY_FAN,
    TEMP_CONTROL_DISPLAY_TEMP,
    TEMP_CONTROL_DISPLAY_FAN
};


PwmOut fan(PB_0);

RunMode mode = RunMode::TEMP_CONTROL_DISPLAY_FAN;


const unsigned int MAX_RPM = 2000;
const float KP = 0.2f;
const float KI = 0.01f;
const float KD = 0.001f;

unsigned int currentRpm = 0;

// Control variables
float integral = 0.0;
float previousError = 0.0;


Timer lastDisplayUpdate;
int displayUpdateInterval = 500000;

Timer controlTimer;
int controlUpdateInterval = 100000;

void IncrementMode();
void SetFanRpm(unsigned int targetRpm);

int main() {
    
    ButtonInput_Init();
    RotaryInput_Init();
    TachoInput_Init();

    IncrementMode();

    lastDisplayUpdate.start();
    controlTimer.start();

    // 2kHz pwm signal
    fan.period_us(500);

    while (true) {
    
        if (HasButtonBeenPressed()) {
            IncrementMode();
        }

       switch (mode) {
        case PC_CONTROL_DISPLAY_PC: {

                int rotaryPosition = RotaryInput_GetPosition();
                int rotaryPc = rotaryPosition * 7;
                if (rotaryPc > 99) {
                    rotaryPc = 99;
                }

                float rotaryP = rotaryPc / 100.0f;
             
                DisplayTwoDigitInteger(rotaryPc);

                if (controlTimer.elapsed_time().count() > controlUpdateInterval) {
                    controlTimer.reset();

                    unsigned int newRpm = TachoInput_GetRpm();
                    printf("RPM: %d\n", newRpm);
                    unsigned int diff;

                    if (newRpm > currentRpm) {
                        diff = newRpm - currentRpm;
                    } else {
                        diff = currentRpm - newRpm;
                    }

                    if (diff < 3000 && newRpm < 3000) {
                        // only accept rpm update if its a sensible change
                        currentRpm = newRpm;
                    } else {
                        //printf("BAD CHANGE: %d\n", newRpm - currentRpm);
                    }
                    

                    SetFanRpm(rotaryP * MAX_RPM);
                }


                break;
            }
        case PC_CONTROL_DISPLAY_FAN: {

                 int rotaryPosition = RotaryInput_GetPosition();


                int rotaryPc = rotaryPosition * 7;
                if (rotaryPc > 99) {
                    rotaryPc = 99;
                }
             
                
               
                fan.write((float)rotaryPosition/ 100.0f);

               // int encoderFrequency = TachoInput_GetSpeed();
                /*
                if (lastDisplayUpdate.elapsed_time().count() > displayUpdateInterval) {
                    lastDisplayUpdate.reset();

                     if (encoderFrequency > 99) {
                        DisplayTwoDigitInteger(99);
                    } else {
                        DisplayTwoDigitInteger(encoderFrequency);
                    }
                }*/
               
                

                
                // print updates
               // printf("ENCODER %d FREQUENCY: %d\n", rotaryPosition, (int)encoderFrequency);

            
            break;
            }
        case TEMP_CONTROL_DISPLAY_TEMP: {
                int temp = ReadTemperature();

                DisplayTwoDigitInteger(temp);
                break;
            }
        default:
            
            break;

       }
            
    }
}


void IncrementMode() {

    switch (mode) {
        case PC_CONTROL_DISPLAY_PC:
            DisplaySeparateChars(11, 16);
            mode = PC_CONTROL_DISPLAY_FAN;
            break;
        case PC_CONTROL_DISPLAY_FAN:
            DisplaySeparateChars(12, 16);
            mode = TEMP_CONTROL_DISPLAY_TEMP;
            break;
        case TEMP_CONTROL_DISPLAY_TEMP:
            DisplaySeparateChars(13, 16);
            mode = TEMP_CONTROL_DISPLAY_FAN;
            break;
        default:
            DisplaySeparateChars(10, 16);
            mode = PC_CONTROL_DISPLAY_PC;
            break;
            
    }

    ThisThread::sleep_for(1000ms);
}

void SetFanRpm(unsigned int targetRpm) {

    int error = targetRpm - currentRpm;

    // Calculate control signal (in this case, a simple proportional control)
    float pTerm = KP * error;
    
    integral += error * KI;

    // Derivative term
    float dTerm = KD * (error - previousError);
    previousError = error;

    int controlSignal = pTerm; //+ integral + dTerm;

    fan.pulsewidth_us(controlSignal);

    printf("CONTROL: TARGET %u CURRENT %u ERROR %d OUTPUT %d - P %d I %d D %d \n", targetRpm, currentRpm, error, controlSignal, (int) pTerm, (int) integral, (int) dTerm);
            
}