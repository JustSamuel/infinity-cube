//
// Created by Samuel on 13/11/2020.
//
#pragma once

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
    CRGB* array[STRIP_LEN];

    // Create a Segment without specifying the pointers.
    Segment(){};

    // Create a Segment by specifying the pointers.
    Segment(CRGB* pointers[]);

    /**
     * Give every LED in the Segment the same color.
     * @param CRGB color to set.
     */
    void setUniformCRGB(CRGB) override;

    /**
     * @return the amount of LEDS in this Segment
     */
    int getLength() override;
};

template<int STRIP_LEN>
Segment<STRIP_LEN>::Segment(CRGB* pointers[])
{
    for (int i = 0; i < STRIP_LEN; ++i)
    {
        array[i] = indices[i];
    }
}

template<int STRIP_LEN>
void Segment<STRIP_LEN>::setUniformCRGB(CRGB color)
{
    for (int i = 0; i < STRIP_LEN; ++i)
    {
        *(array[i]) = color;
    }
}

template<int STRIP_LEN>
int Segment<STRIP_LEN>::getLength()
{
    return STRIP_LEN;
}