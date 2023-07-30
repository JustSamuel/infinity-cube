//
// Created by Samuel on 25/03/2021.
//
#pragma once
#include <FastLED.h>
#include "Config.h"

/**
 * Class wrapper for the JSON input.
 */
class AnimationCommand {
protected:

public:
    AnimationCommand() = default;

    // id of what animation to show.
    volatile long animationId = 0;

    // Color provided by the JSON.
    volatile CRGB color;

    // For displaying raw leds.
    volatile int raw[NUM_LEDS] = {};

    // Used by the GitLabAnimation.
    volatile int changes = 0;

    // Used by the Leap animation.
    volatile double xfloat = 0.0;

    // Used by the Leap animation.
    volatile double height = 0.0;

    // If new Input has been supplied.
    volatile bool hasNewInput = false;
};