//
// Created by Samuel on 13/11/2020.
//
#pragma once
#include "LEDController.h"
#include "Config.h"

//Syntactic sugar
#define leds LEDController::getInstance()->ledArray
#define fCube LEDController::getInstance()->fullCube
#define fStrips LEDController::getInstance()->strips

/**
 * Use to retrieve the relevant pointers for the segment at index int.
 */
int* getIndicesFromIndex(int);

/**
 * Used for steps in animation. Pushes the FastLed and writes full black to it.
 * @param sleep Used to control animation speed.
 */
void display(int sleep, bool clear = true);

/**
 * Uses Fisher-Yates algorithm to shuffle the array.
 * @param array to shuffle.
 */
void shuffle(int array[], int length);

/**
 * Parses an integer value to an rgb array.
 * @param array The target array.
 * @param color The integer representation of the color.
 */
void intToRGB(int array[], int color);

/**
 * Helper function that calculates the gaussian value.
 * @param x The X coordinate for which to calculate.
 * @param a The peak of the curve
 * @param b The offset of the curve
 * @param c The variance of the curve.
 */
double getGaussianValue(int x, double a, double b, double c);