//
// Created by Samuel on 13/11/2020.
//
#pragma once
#include "InfintyCube.h"
#include "Helper.h"

LEDController *LEDController::instance = nullptr;

LEDController::LEDController() {
    ledArray = new CRGB[NUM_LEDS];
    CFastLED::addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(ledArray, NUM_LEDS).setCorrection(TypicalLEDStrip);
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

void LEDController::defaults()
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

void LEDController::parseCommand(int command, int* color, int params[]) {
    switch (command) {
        case 0:
            doAnimation = false;
            display(10, true);
            break;
        case 1:
            doAnimation = true;
            currentAnimation = new TestAnimation(fCube);
            break;
        case 2:
            doAnimation = false;
            CRGB currentColor = CRGB(color[0],color[1],color[2]);
            GitLabAnimation(fCube, currentColor, params[0]).draw();
            display(10, false);
            break;
    }
}

LEDController *LEDController::getInstance() {
    if (!instance) {
        instance = new LEDController();
    }
    return instance;
}
