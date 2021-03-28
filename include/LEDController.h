//
// Created by Samuel on 13/11/2020.
//
#pragma once
#include <ArduinoJson.h>
#include "AnimationCommand.h"
#include "SegmentBase.h"
#include "Config.h"

// Forward declaration to prevent cyclic dependency.
class Animation;

/**
 * Singleton LEDController class used as wrapper for Segments to represent the LEDController.
 */
class LEDController {
    // Singleton instance of this LEDController.
    static LEDController *instance;

    // Normalize directions of the segments strips.
    const int TO_INVERT[12] = {0, 1, 4, 5, 8, 9, 12, 15, 16, 19, 20, 21};

    // Private Constructor.
    LEDController();

public:
    // Singleton constructor.
    static LEDController *getInstance();

    // All the leds in the controller as a single segment.
    SegmentBase* fullCube;

    // Every Segment of the controller in an array.
    SegmentBase *strips[SEGMENT_COUNT]{};


    // Returns the LEDController to the default pre-defined states.
    void defaults();

    // Parses string commands.
    void parseCommand();

    // Toggles the animation on or off.
    boolean doAnimation = true;

    // Current animation running on the controller.
    Animation* currentAnimation = nullptr;

    // The LED array used by FastLED library.
    CRGB* ledArray;

    [[noreturn]] static void testBench(void * parameter);

    // Current params.
    AnimationCommand* currentCommand;

};