//
// Created by Samuel on 13/11/2020.
//
#pragma once

/**
 * Singleton Cube class used as wrapper for Segments to represent the Cube.
 */
class Cube {
    // Singleton instance of this Cube.
    static Cube *instance;

    // Private Constructor.
    Cube();

public:

    // Singleton constructor.
    static Cube *getInstance();

    // The LED array used by FastLED library.
    CRGB* ledArray;
};