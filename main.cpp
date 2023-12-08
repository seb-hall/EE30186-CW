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

// SDA SCL
I2C tempSensor(PB_14, PB_13);
const int addr7Bit = 0x4D; // Shift the address for mbed I2C library
const int addr = 0x4D << 1; // Shift the address for mbed I2C library


//PwmOut fan(PB_0);

char SevenSegmentHexFromInt(char digit) {
    switch (digit) {
        case 0:
            return DISP_0;
        case 1:
            return DISP_1;
        case 2:
            return DISP_2;
        case 3:
            return DISP_3;
        case 4:
            return DISP_4;
        case 5:
            return DISP_5;
        case 6:
            return DISP_6;
        case 7:
            return DISP_7;
        case 8:
            return DISP_8;
        case 9:
            return DISP_9;
    }

    return DISP_NULL;
}

int main() {
    
    
     char cmd[2];
    while (1) {
        cmd[0] = 0x00; // Temperature register
        tempSensor.write(addr, cmd, 1); // Send temperature register address
        tempSensor.read(addr, cmd, 1);  // Read one byte from the temperature register

        // Convert the byte to an integer
        int temp = static_cast<int8_t>(cmd[0]); // Cast to signed type to handle 2's complement

        // Print temperature in decimal and binary
        printf("\nTemperature: %d C, Binary: ", temp);
        
        leftDisplay = SevenSegmentHexFromInt(temp / 10);
        rightDisplay = SevenSegmentHexFromInt(temp % 10);
        ThisThread::sleep_for(1000); // Wait for 1 second

    }
    



    /*
    
    while (true) {

        //  get updates
        int encoderPosition = RotaryInput_GetPosition();

        //fan.write(0.1f * (float) encoderPosition);
        //fan.pulsewidth_us(encoderPosition);

        int encoderFrequency = TachoInput_GetSpeed();
        // print updates
        //printf("POSITION: %d FREQUENCY: %d\n", encoderPosition, (int)encoderFrequency);
    }*/
}
