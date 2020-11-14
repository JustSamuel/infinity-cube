//
// Created by Samuel on 13/11/2020.
//
#pragma once

//Syntactic sugar
#define leds Cube::getInstance()->ledArray

/**
 * Use to retrieve the relevant pointers for the segment at index int.
 */
CRGB** getSegmentFromIndex(int);