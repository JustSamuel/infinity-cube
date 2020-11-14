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
}

Cube *Cube::getInstance() {
    if (!instance) {
        instance = new Cube();
    }
    return instance;
}