//  main.cpp
//  EE30186 CW
//
//  This file is the program entry point and controls the overall
//  program control flow

#include "mbed.h"
#include "RotaryInput.h"
#include "TachoInput.h"
#include "LCD_ST7066U.h"

PwmOut contrast(PB_5);


/*
//PwmOut fan(PB_0);

int main() {

    LCD lcd(PB_15, PB_14, D0, D1, D2, D3); // rs, e, d4-d7

    lcd.clear();
    lcd.write("a");



    while(1)
    {
        // code
    }

   
    //  initialize modules
    //RotaryInput_Init();
    //TachoInput_Init();

    contrast.period_us(20);

    fan.period_us(20);  // 4 second period
         // 50% duty cycle, relative to period
    contrast.pulsewidth_us(1);
    while (true) {
        //  get updates
        int encoderPosition = RotaryInput_GetPosition();

        //fan.write(0.1f * (float) encoderPosition);
        fan.pulsewidth_us(encoderPosition);

        int encoderFrequency = TachoInput_GetSpeed();
        // print updates
        //printf("POSITION: %d FREQUENCY: %d\n", encoderPosition, (int)encoderFrequency);
    }
}*/


// Define the LCD control pins
DigitalOut rs(PB_15);  // Register Select
DigitalOut en(PB_14); // Enable
BusOut data(D0, D1, D2, D3); // D4, D5, D6, D7

// Function to send command to LCD
void lcdCommand(char command) {
    rs = 0;          // Set for command mode
    data = command >> 4; // Send higher nibble
    en = 1; wait_us(1); en = 0; wait_us(45); // Pulse the enable pin
    data = command & 0x0F; // Send lower nibble
    en = 1; wait_us(1); en = 0; ThisThread::sleep_for(2ms); // Pulse the enable pin
}

// Function to initialize the LCD
void initLCD() {
    ThisThread::sleep_for(15ms); // Wait for LCD to power up
    lcdCommand(0x03); ThisThread::sleep_for(5ms); // Function set (8-bit mode), but wait after
    lcdCommand(0x03); wait_us(100); // Function set (8-bit mode) again
    lcdCommand(0x03); // Function set (8-bit mode) third time
    lcdCommand(0x02); // Set to 4-bit mode

    lcdCommand(0x28); // Function Set: 4-bit mode, 2 lines, 5x8 dots
    lcdCommand(0x0C); // Display ON, Cursor OFF, Blink OFF
    lcdCommand(0x01); // Clear Display
    lcdCommand(0x06); // Entry Mode: Increment cursor, No shift
}

// Function to create and load a custom character
void createCustomChar() {
    // Custom character (a simple pattern in 5x8 matrix)
    char customChar[8] = {0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00};

    lcdCommand(0x40); // Set CGRAM address to 0 (start of custom char memory)
    rs = 1; // Set for data mode
    for (int i = 0; i < 8; i++) {
        data = customChar[i] >> 4; // Higher nibble
        en = 1; wait_us(1); en = 0; wait_us(45); // Pulse enable
        data = customChar[i] & 0x0F; // Lower nibble
        en = 1; wait_us(1); en = 0; ThisThread::sleep_for(2ms); // Pulse enable
    }
}

int main() {

    
    contrast.period_us(50);

    contrast.pulsewidth_us(2);

    initLCD();
    createCustomChar();

    // Display the custom character (stored in location 0)
    lcdCommand(0x80); // Set DDRAM address to 0 (first character of first line)
    rs = 1; // Set for data mode
    data = 0x00 >> 4; // Custom character is at 0x00
    en = 1; wait_us(1); en = 0; wait_us(45);
    data = 0x00 & 0x0F;
    en = 1; wait_us(1); en = 0; ThisThread::sleep_for(2ms);

    while (true) {
        // Your loop code here
    }
}
