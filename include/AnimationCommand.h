//
// Created by Samuel on 25/03/2021.
//
#pragma once
#include <FastLED.h>

/**
 * Class wrapper for the JSON input.
 */
class AnimationCommand {
protected:

public:
    AnimationCommand() = default;

    // id of what animation to show.
    long animationId = 0;

    // Color provided by the JSON.
    CRGB color;

    // correction bit for the animationId.
    bool setAnimation = false;

    // Used by the GitLabAnimation.
    int changes = 0;

    // Used by the Leap animation.
    double xfloat = 0.0;

    // Used by the Leap animation.
    double height = 0.0;

    // If new Input has been supplied.
    bool hasNewInput = false;
};