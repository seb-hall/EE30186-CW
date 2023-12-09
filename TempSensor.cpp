#include "TempSensor.h"

// SDA SCL
static I2C tempSensor(PB_14, PB_13);

// 7 bit address 0x4D shifted left by 1 bit
const static int addr = 0x4D << 1;

static char cmd[2];

int ReadTemperature() {
    cmd[0] = 0x00; // Temperature register
    tempSensor.write(addr, cmd, 1); // Send temperature register address
    tempSensor.read(addr, cmd, 1);  // Read one byte from the temperature register

    // Convert the byte to an integer
    return static_cast<int8_t>(cmd[0]); // Cast to signed type to handle 2's complement
}