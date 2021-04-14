#include <Arduino.h>
#include "InfintyCube.h"

void setup() {
    // Failsafe
    delay(3000);
    Serial.begin(115200);

    // Initialize the controller to defaults.
    LEDController::getInstance()->defaults();

    // Also initializes the WiFiServer.
    CServer::getInstance();

    // Clear the LEDStrip.
    display(10);
}

void loop() {
//    // Get pointer to the current command.
    AnimationCommand *current = LEDController::getInstance() -> currentCommand;
    if(current -> hasNewInput) {
        LEDController::getInstance() -> parseCommand();
    }
//
//    // Read params from the command
//    fCube->setCRGB(current->color, (int)(fCube->getLength() * current->xfloat));

    // Display + delay(10)
//    display(10, false);
}