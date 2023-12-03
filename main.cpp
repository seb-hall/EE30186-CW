//  main.cpp
//  EE30186 CW
//
//  This file is the program entry point and controls the overall
//  program control flow

#include "mbed.h"
#include "RotaryInput.h"
#include "TachoInput.h"
#include "TextLCD.h"

PwmOut contrast(PB_5);

//PwmOut fan(PB_0);

int main() {

    TextLCD lcd(PB_15, PB_14, PB_10, PA_8, PB_2, PB_1, TextLCD::LCD16x1); // rs, e, d4-d7

    lcd.cls();
    lcd.printf("A");
    


   
    //  initialize modules
    //RotaryInput_Init();
    //TachoInput_Init();

    contrast.period_us(20);

    //fan.period_us(20);  // 4 second period
         // 50% duty cycle, relative to period
    contrast.pulsewidth_us(10);

     lcd.cls();
    lcd.printf("HOME");


    while (true) {
        //  get updates
        int encoderPosition = RotaryInput_GetPosition();

        //fan.write(0.1f * (float) encoderPosition);
        //fan.pulsewidth_us(encoderPosition);

        int encoderFrequency = TachoInput_GetSpeed();
        // print updates
        //printf("POSITION: %d FREQUENCY: %d\n", encoderPosition, (int)encoderFrequency);
    }
}
