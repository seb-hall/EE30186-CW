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

#include <deque>

enum RunMode {
    PC_CONTROL_DISPLAY_PC,
    PC_CONTROL_DISPLAY_FAN,
    TEMP_CONTROL_DISPLAY_TEMP,
    TEMP_CONTROL_DISPLAY_FAN
};


PwmOut fan(PB_0);

RunMode mode = RunMode::TEMP_CONTROL_DISPLAY_FAN;

const unsigned int MAX_RPM = 2300;
const unsigned int MAX_RPM_CHANGE_ALLOWED = 3000;
const unsigned int MAX_RPM_READING_ALLOWED = 3000;
const float KP = 0.2f;

unsigned int currentRpm = 0;

std::deque<int> rpmBuffer;
const size_t bufferSize = 20; // Size of the moving average buffer
unsigned int smoothedRpm = 0;

Timer displayUpdateTimer;
int displayUpdateInterval = 1000000;

Timer controlTimer;
int controlUpdateInterval = 100000;

void IncrementMode();
void UpdateRpm();
void UpdateSmoothedRpm();
void SetFanRpm(unsigned int targetRpm);
unsigned int RequestRpmFromTemp(int temp);

int main() {
    
    ButtonInput_Init();
    RotaryInput_Init();
    TachoInput_Init();

    IncrementMode();

    displayUpdateTimer.start();
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
                    
                    UpdateRpm();

                    SetFanRpm(rotaryP * MAX_RPM);
                    
                    UpdateSmoothedRpm();
                }

                if (displayUpdateTimer.elapsed_time().count() > displayUpdateInterval) {
                    displayUpdateTimer.reset();

                    
                }


                break;
            }
        case PC_CONTROL_DISPLAY_FAN: {

                int rotaryPosition = RotaryInput_GetPosition();
                int rotaryPc = rotaryPosition * 7;
                if (rotaryPc > 99) {
                    rotaryPc = 99;
                }

                float rotaryP = rotaryPc / 100.0f;
             
                if (controlTimer.elapsed_time().count() > controlUpdateInterval) {
                    controlTimer.reset();
                    
                    UpdateRpm();

                    SetFanRpm(rotaryP * MAX_RPM);
                    
                    UpdateSmoothedRpm();
                }

                if (displayUpdateTimer.elapsed_time().count() > displayUpdateInterval) {
                    displayUpdateTimer.reset();

                    int fanSpeedPc = (smoothedRpm * 100) / MAX_RPM;
                    DisplayTwoDigitInteger(fanSpeedPc);
                    //printf("FAN SPEED SMOOTH %d\n", fanSpeedPc);
                }



            
            break;
            }
        case TEMP_CONTROL_DISPLAY_TEMP: {

                int temp = ReadTemperature();

                if (controlTimer.elapsed_time().count() > controlUpdateInterval) {
                    controlTimer.reset();
                    
                    UpdateRpm();

                    int targetRpm = RequestRpmFromTemp(temp);

                    SetFanRpm(targetRpm);
                    
                    UpdateSmoothedRpm();
                }

                if (displayUpdateTimer.elapsed_time().count() > displayUpdateInterval) {
                    displayUpdateTimer.reset();

                    DisplayTwoDigitInteger(temp);
                }

                break;
            }
        default:

        
            int temp = ReadTemperature();

            if (controlTimer.elapsed_time().count() > controlUpdateInterval) {
                controlTimer.reset();
                
                UpdateRpm();

                int targetRpm = RequestRpmFromTemp(temp);

                SetFanRpm(targetRpm);
                
                UpdateSmoothedRpm();
            }

            if (displayUpdateTimer.elapsed_time().count() > displayUpdateInterval) {
                displayUpdateTimer.reset();

                int fanSpeedPc = (smoothedRpm * 100) / MAX_RPM;
                DisplayTwoDigitInteger(fanSpeedPc);
            }

            break;

       }
            
    }
}


void IncrementMode() {

    SetFanRpm(0);

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

void UpdateRpm() {
    unsigned int newRpm = TachoInput_GetRpm();
    unsigned int diff;

    if (newRpm > currentRpm) {
        diff = newRpm - currentRpm;
    } else {
        diff = currentRpm - newRpm;
    }

    if (diff < MAX_RPM_CHANGE_ALLOWED && newRpm < MAX_RPM_READING_ALLOWED) {
        // only accept rpm update if its a sensible change
        currentRpm = newRpm;
    }
}

void SetFanRpm(unsigned int targetRpm) {

    int error = targetRpm - currentRpm;

    // Calculate control signal
    int controlSignal = KP * error;

    fan.pulsewidth_us(controlSignal);

    //printf("CONTROL: TARGET %u CURRENT %u ERROR %d OUTPUT %d\n", targetRpm, currentRpm, error, controlSignal);
            
}

void UpdateSmoothedRpm() {
    // Add new RPM value to the buffer
    rpmBuffer.push_back(currentRpm);

    // If the buffer exceeds the size limit, remove the oldest value
    if (rpmBuffer.size() > bufferSize) {
        rpmBuffer.pop_front();
    }

    // Calculate the average
    int sum = 0;
    for (int rpm : rpmBuffer) {
        sum += rpm;
    }

    smoothedRpm = sum / rpmBuffer.size();

}

unsigned int RequestRpmFromTemp(int temp) {
    if (temp <= 20) {
        return 0;
    } else if (temp >= 30) {
        return MAX_RPM;
    } else {
        // Linear interpolation
        return (unsigned int)(MAX_RPM * (temp - 20) / 10.0);
    }
}