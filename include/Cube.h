//
// Created by Samuel on 13/11/2020.
//
#pragma once
#include "SegmentBase.h"
#include "Config.h"

/**
 * Singleton Cube class used as wrapper for Segments to represent the Cube.
 */
class Cube {
    // Singleton instance of this Cube.
    static Cube *instance;

    // Private Constructor.
    Cube();

public:

    // All the leds in the cube as a single segment.
    SegmentBase* fullCube;

    // Every Segment of the cube in an array.
    SegmentBase *strips[SEGMENT_COUNT];

    // Singleton constructor.
    static Cube *getInstance();

    // Returns the Cube to the default pre-defined states.
    void defaults();

    // The LED array used by FastLED library.
    CRGB* ledArray;
};