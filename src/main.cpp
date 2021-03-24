#include <Arduino.h>
#include "InfintyCube.h"

Animation* currentAnimation;

void setup() {
    delay(3000);
    Serial.begin(115200);

    LEDController::getInstance()->defaults();
    LEDController::getInstance() -> currentAnimation = new TestAnimation(fCube);
    CServer::getInstance();

    display(10);
}

void loop() {
    if (LEDController::getInstance() -> doAnimation) {
        LEDController::getInstance() -> currentAnimation -> draw();
    } else {
        display(10, false);
    }
}