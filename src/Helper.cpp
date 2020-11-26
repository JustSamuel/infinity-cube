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
 * Show the current array, sleep to update the leds and then right full black to the cube.
 * @param sleep time to wait
 */
void display(int sleep, bool clear){
    FastLED.show();
    delay(sleep);
    if (clear) fCube->setUniformCRGB(CRGB::Black);
}

void shuffle(int array[], int length){
    for (int i = length; i != 0; i--) {
        int j = random(0, i);
        int temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }
};