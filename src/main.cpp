#include <Arduino.h>
#include "InfintyCube.h"

SegmentBase *strips[SEGMENT_COUNT];


void setup() {
    delay(3000);
    Serial.begin(115200);

    for (int i = 0; i < SEGMENT_COUNT; ++i) {
        CRGB **pointers = getSegmentFromIndex(i);
        strips[i] = new Segment<SEGMENT_SIZE>(pointers);
        delete[] pointers;
    }
}

void loop() {
    for (int i = 0; i < 255; ++i) {
        for (auto &strip : strips) {
            strip->setUniformCRGB(CRGB(i, 0, 0));
        }
        FastLED.show();
        delay(10);
    }
    FastLED.show();
    for (int i = 255; i >= 0; i--) {
        for (auto &strip : strips) {
            strip->setUniformCRGB(CRGB(i, 0, 0));
        }
        FastLED.show();
        delay(10);
    }
    FastLED.show();
    delay(100);
}