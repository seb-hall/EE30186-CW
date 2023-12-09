#include "ButtonInput.h"


static InterruptIn buttonInput(BUTTON1);
static Timer timeSinceLastButtonDown;

static bool hasButtonBeenPressed = false;

static void ButtonDown();

void ButtonInput_Init() {
    timeSinceLastButtonDown.start();

    buttonInput.rise(ButtonDown);
}


//  return if button has been pressed since the last call
//  resets to false after the function is called
bool HasButtonBeenPressed() {
    if (hasButtonBeenPressed) {
        hasButtonBeenPressed = false;
        return true;
    } else {
        return false;
    }
}

static void ButtonDown() {
    
    // check if a few ms have elapsed since the last change
    if (std::chrono::duration_cast<std::chrono::milliseconds>
        (timeSinceLastButtonDown.elapsed_time()) > buttonDebounceTime) { 

        hasButtonBeenPressed = true;
        timeSinceLastButtonDown.reset();
    }
}