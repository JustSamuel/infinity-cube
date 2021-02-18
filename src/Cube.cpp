//
// Created by Samuel on 13/11/2020.
//
#pragma once
#include "InfintyCube.h"

Cube *Cube::instance = nullptr;

Cube::Cube() {
    ledArray = new CRGB[NUM_LEDS];
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(ledArray, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    int indices[NUM_LEDS];
    for (int i = 0; i < NUM_LEDS; ++i) {
        indices[i] = i;
    }

    fullCube = new Segment<NUM_LEDS>(indices);

    for (int i = 0; i < SEGMENT_COUNT; ++i) {
        int* fromIndex = getIndicesFromIndex(i);
        strips[i] = new Segment<SEGMENT_SIZE>(fromIndex);
        delete[] fromIndex;
    }
}

void Cube::defaults()
{
    // Default is full black.
    fullCube->setUniformCRGB(CRGB::Red);

    // Set default directions
    for (auto & strip : strips) {
        strip -> setReversed(false);
    }

    for (int j = 0; j < 12; ++j) {
//        strips[TO_INVERT[j]] -> setReversed(true);
    }
}

Cube *Cube::getInstance() {
    if (!instance) {
        instance = new Cube();
    }
    return instance;
}