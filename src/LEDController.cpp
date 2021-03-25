//
// Created by Samuel on 13/11/2020.
//
#pragma once

#include <LEDController.h>
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


void LEDController::parseCommand() {
    switch (currentCommand -> animationId) {
        case 0:
            doAnimation = false;
            break;
        case 1:
            doAnimation = true;
            currentAnimation = new TestAnimation(fCube);
            break;
        case 2:
            doAnimation = false;
            GitLabAnimation(fCube, currentCommand -> color, currentCommand-> changes).draw();
            break;
        case 3:
            fCube->drawGaussian(&currentCommand-> color, 1, fCube->getLength()*currentCommand-> xfloat, currentCommand -> height);
            break;
        default:
            break;
    }
}

LEDController *LEDController::getInstance() {
    if (!instance) {
        instance = new LEDController();
    }
    return instance;
}