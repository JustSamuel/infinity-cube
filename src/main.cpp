#include <Arduino.h>
#include "InfintyCube.h"

Animation* currentAnimation;

void setup() {
    delay(3000);
    Serial.begin(115200);
    Cube::getInstance()->defaults();
    display(10);
    currentAnimation = new TestAnimation(fCube);
    ConnectToWiFi();
}

void loop() {
    currentAnimation -> draw();
}