//
// Created by Samuel on 13/11/2020.
//
#pragma  once
#include "InfintyCube.h"
#include "Helper.h"

/**
 * Returns an array of pointers on the heap for a index based segment. Intuitively the cube is split into 24 segments
 * of 11 leds each.
 *
 * @param index Which of the 24 segments it should be.
 * @return array of pointers to leds representing the segment.
 */
int* getIndicesFromIndex(int index){
    // Allocate array on heap
    int* indices = new int[SEGMENT_SIZE];

    // Fill array with the correct pointers.
    for (int i = 0; i < SEGMENT_SIZE; ++i) {
        indices[i] = i + SEGMENT_SIZE * index;
    }

    return indices;
}

/**
 * Show the current array, sleep to update the leds and then write full black to the cube.
 * @param sleep time to wait
 * @param clear whether to make all leds black or not.
 */
void display(int sleep, bool clear){
    if (clear) fCube->setUniformCRGB(CRGB::Black);
    FastLED.show();
    delay(sleep);
}

void shuffle(int array[], int length){
    for (int i = length; i != 0; i--) {
        int j = random(0, i);
        int temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }
}

void intToRGB(int* array, int color) {
    array[0] = (color & 0xFF0000) >> 16;
    array[1] = (color & 0xFF00) >> 8;
    array[2] = (color & 0xFF);
}

double getGaussianValue(int x, double a, double b, double c) {
    double factor = a * exp(-1 * (pow((x - b), 2) / (2 * pow(c, 2))));
    return factor;
}