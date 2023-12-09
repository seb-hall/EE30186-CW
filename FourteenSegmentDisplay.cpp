#include "FourteenSegmentDisplay.h"


// A1 B1 C1 D1 E1 F1 G1
BusOut rightDisplay(D2, D3, D4, D5, D6, D7, D8);

// A2 B2 C2 D2 E2 F2 G2
BusOut leftDisplay(D9, D10, D11, D12, D13, D14, D15);


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

char SevenSegmentHexFromChar(char digit) {
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
        case 10:
            return DISP_A;
        case 11:
            return DISP_B;
        case 12:
            return DISP_C;
        case 13:
            return DISP_D;
        case 14:
            return DISP_E;
        case 15:
            return DISP_F;

    }

    return DISP_NULL;
}



void DisplayTwoDigitInteger(int integer) {
    leftDisplay = SevenSegmentHexFromChar(integer / 10);
    rightDisplay = SevenSegmentHexFromChar(integer % 10);
}

void DisplaySeparateChars(char left, char right) {
    leftDisplay = SevenSegmentHexFromChar(left);
    rightDisplay = SevenSegmentHexFromChar(right);
}