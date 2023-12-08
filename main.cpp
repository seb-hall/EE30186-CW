//  main.cpp
//  EE30186 CW
//
//  This file is the program entry point and controls the overall
//  program control flow

#include "mbed.h"
#include "RotaryInput.h"
#include "TachoInput.h"




#define DISP_NULL 0xFF
#define DISP_0 0xC0
#define DISP_1 0xF9
#define DISP_2 0xA4
#define DISP_3 0xB0
#define DISP_4 0x99
#define DISP_5 0x92
#define DISP_6 0x82
#define DISP_7 0xF8
#define DISP_8 0x00
#define DISP_9 0x90
#define DISP_A 0x88
#define DISP_B 0x83
#define DISP_C 0xC6
#define DISP_D 0xA1
#define DISP_E 0x86
#define DISP_F 0x8E

// A1 B1 C1 D1 E1 F1 G1
BusOut rightDisplay(D2, D3, D4, D5, D6, D7, D8);

// A2 B2 C2 D2 E2 F2 G2
BusOut leftDisplay(D9, D10, D11, D12, D13, D14, D15);


//PwmOut fan(PB_0);

int main() {

    //TextLCD lcd(PB_15, PB_14, PB_10, PA_8, PB_2, PB_1, TextLCD::LCD16x1); // rs, e, d4-d7
    //LCD lcd(PB_15, PB_14, PB_10, PA_8, PB_2, PB_1);

    //lcd.printf("A");
    

            //lcd.clear();
    //lcd.writeCharacter('G');
   
    //  initialize modules
    //RotaryInput_Init();
    //TachoInput_Init();

    //contrast.period_us(20);

    //fan.period_us(20);  // 4 second period
         // 50% duty cycle, relative to period
    //contrast.pulsewidth_us(0);

    
    //lcd.printf("HOME");



    leftDisplay = DISP_F;
    rightDisplay = DISP_0;


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
