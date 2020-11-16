//
// Created by Samuel on 13/11/2020.
//
#pragma once
#include "Cube.h"
#include "Config.h"

//Syntactic sugar
#define leds Cube::getInstance()->ledArray

/**
 * Use to retrieve the relevant pointers for the segment at index int.
 */
int* getIndicesFromIndex(int);