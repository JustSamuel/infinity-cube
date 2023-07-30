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

    currentCommand = new AnimationCommand();

    int indices[NUM_LEDS];
    for (int i = 0; i < NUM_LEDS; ++i) {
        indices[i] = i;
    }

    fullCube = new Segment<NUM_LEDS>(indices);

    for (int i = 0; i < SEGMENT_COUNT; ++i) {
        int *fromIndex = getIndicesFromIndex(i);
        strips[i] = new Segment<SEGMENT_SIZE>(fromIndex);
        delete[] fromIndex;
    }

    xMutexB = xSemaphoreCreateMutex();
    xMutexA = xSemaphoreCreateMutex();
}

void LEDController::defaults() {
    // Default is full black.
    fullCube->setUniformCRGB(CRGB::Red);

    // Set default directions
    for (auto &strip : strips) {
        strip->setReversed(false);
    }

    for (int j = 0; j < 12; ++j) {
//        strips[TO_INVERT[j]] -> setReversed(true);
    }
}

void LEDController::parseCommand() {
    xSemaphoreTake(LEDController::getInstance()->xMutexB, 0);
    LEDController::getInstance()->currentCommand->hasNewInput = false;
    int animationId = LEDController::getInstance()->currentCommand->animationId;
    CRGB color = CRGB(LEDController::getInstance()->currentCommand->color.r,
                      LEDController::getInstance()->currentCommand->color.g,
                      LEDController::getInstance()->currentCommand->color.b);
    double x = fCube->getLength() * LEDController::getInstance()->currentCommand->xfloat;
    double height = LEDController::getInstance()->currentCommand->height;
    int raw[NUM_LEDS] = {};
    std::copy(LEDController::getInstance()->currentCommand->raw, LEDController::getInstance()->currentCommand->raw + NUM_LEDS, raw);
    xSemaphoreGive(LEDController::getInstance()->xMutexA);

    switch (animationId) {
        case 0:
            doAnimation = false;
            break;
        case 1:
            doAnimation = true;
            currentAnimation = new TestAnimation(fCube);
            break;
        case 2:
            doAnimation = false;
            GitLabAnimation(fCube, color, currentCommand->changes).draw();
            break;
        case 3:
            currentAnimation = nullptr;
            fCube->drawGaussian(color, 1, x, height);
            break;
        case 4:
            doAnimation = true;
            currentAnimation = new AlarmAnimation(fCube);
            break;
        case 5:
            doAnimation = false;
            int colorArr[3];
            for (int i = 0; i < NUM_LEDS; ++i) {
                intToRGB(colorArr, raw[i]);
                leds[i] = CRGB(colorArr[0], colorArr[1], colorArr[2]);
            }
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