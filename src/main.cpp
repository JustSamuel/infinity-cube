#include <Arduino.h>
#include "InfintyCube.h"

void setup() {
    delay(3000);
    Serial.begin(115200);

    LEDController::getInstance() -> currentAnimation = new TestAnimation(fCube);
    CServer::getInstance();
    display(10);
}

void loop() {
    display(20, false);
}