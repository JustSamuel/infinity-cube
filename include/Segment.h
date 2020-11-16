//
// Created by Samuel on 13/11/2020.
//
#pragma once

#include "Helper.h"
#include "SegmentBase.h"

/**
 * Segment class to represent a segment of LEDS on the strip,
 * The LEDS of the segment are defined by pointers to the FastLED strip.
 *
 * @tparam STRIP_LEN Amount of LEDS in the segment.
 */
template<int STRIP_LEN>
class Segment: public SegmentBase
{
public:
    // The pointers of the LEDS in the segment.
    int indices[STRIP_LEN];

    // Create a Segment without specifying the pointers.
    Segment(){};

    // Create a Segment by specifying the pointers.
    Segment(int indices[]);

    /**
     * @return the amount of LEDS in this Segment
     */
    int getLength();
};

template<int STRIP_LEN>
Segment<STRIP_LEN>::Segment(int ind[])
{
    for (int i = 0; i < STRIP_LEN; ++i)
    {
        indices[i] = ind[i];
    }
}

template<int STRIP_LEN>
int Segment<STRIP_LEN>::getLength()
{
    return STRIP_LEN;
}