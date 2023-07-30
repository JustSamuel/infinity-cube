#include <Arduino.h>
#include "InfintyCube.h"

void setup() {
    // Failsafe
    delay(3000);
    Serial.begin(115200);

    // Initialize the controller to defaults.
    LEDController::getInstance()->defaults();
    LEDController::getInstance()->currentAnimation = new RainAnimation(fCube);

    // Also initializes the WiFiServer.
    CServer::getInstance();

    // Clear the LEDStrip.
    display(10);
}

void loop() {
    // Check if there is new input...
    if (LEDController::getInstance()->currentCommand->hasNewInput) {
        // ...if so, parse it.
        LEDController::getInstance() -> parseCommand();
    }

    // Draw current animation.
    if (LEDController::getInstance()->currentAnimation != nullptr && LEDController::getInstance()->doAnimation) {
        LEDController::getInstance() -> currentAnimation -> draw();
    }

    // Display and sleep.
    display(1, false);
}