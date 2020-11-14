//
// Created by Samuel on 13/11/2020.
//
#pragma once

/**
 * Singleton Cube class
 */
class Cube {
    Cube *instance;

    void setDefaults();

    Cube();

public:

    static Cube *getInstance();

    CRGB* leds;
};