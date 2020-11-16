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
    // Reverses the Segment so the first index is the last.
    boolean reversed = false;

    /**
     * @return the ith index in the array of the Segment.
     */
    int getIndex(int) override;

public:
    // The pointers of the LEDS in the segment.
    int indices[STRIP_LEN];

    // Create a Segment without specifying the pointers.
    Segment(){};

    // Create a Segment by specifying the pointers.
    Segment(int indices[]);

    /**
     * Give every LED in the Segment the same color.
     * @param CRGB color to set.
     */
    void setUniformCRGB(CRGB) override;

    /**
     * Give a single LED a CRGB color.
     * @param CRGB the color to set.
     * @param int the index of the LED.
     */
    void setCRGB(CRGB, int) override;

    /**
     * Reverses direction of indices.
     */
    void reverse() override;

    /**
     * @return the amount of LEDS in this Segment
     */
    int getLength() override;
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
void Segment<STRIP_LEN>::setUniformCRGB(CRGB color)
{
    for (int i = 0; i < STRIP_LEN; ++i)
    {
        leds[indices[i]] = color;
    }
}

template<int STRIP_LEN>
int Segment<STRIP_LEN>::getLength()
{
    return STRIP_LEN;
}

template<int STRIP_LEN>
int Segment<STRIP_LEN>::getIndex(int i)
{
    if (!reversed) {
        return indices[i];
    } else {
        return indices[STRIP_LEN - i - 1];
    }
}

template<int STRIP_LEN>
void Segment<STRIP_LEN>::setCRGB(CRGB color, int i)
{
    leds[getIndex(i)] = color;
}

template<int STRIP_LEN>
void Segment<STRIP_LEN>::reverse() {
    reversed = !reversed;
}
