//
// Created by Samuel on 13/11/2020.
//
#pragma  once
#include "InfintyCube.h"

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