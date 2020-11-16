#include <Arduino.h>
#include "InfintyCube.h"

void setup() {
    delay(3000);
    Serial.begin(115200);
    Cube::getInstance()->defaults();
    FastLED.show();
}

void loop() {
    for (int j = 0; j < SEGMENT_SIZE; ++j) {
        for (int i = 0; i < 255; i = i + 10) {
            for (auto &strip : Cube::getInstance()->strips) {
                strip->setCRGB(CRGB(i, 0, 0), j);
            }
            FastLED.show();
            delay(10);
        }
    }

    for (auto &strip: Cube::getInstance()->strips) {
        strip->reverse();
    }

    FastLED.show();
    for (int i = 255; i >= 0; i--) {
        for (auto &strip : Cube::getInstance()->strips) {
            strip->setUniformCRGB(CRGB(i, 0, 0));
        }
        FastLED.show();
        delay(10);
    }
    FastLED.show();
    delay(100);
}