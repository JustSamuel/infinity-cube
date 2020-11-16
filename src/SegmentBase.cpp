//
// Created by Samuel on 16/11/2020.
//

#pragma once
#include "Helper.h"
#include "SegmentBase.h"

/**
 * @return the ith index in the array of the Segment.
 */
int SegmentBase::getIndex(int i)
{
    if (!reversed) {
        return indices[i];
    } else {
        return indices[getLength() - i - 1];
    }
}

/**
 * Reverse the direction of the array in the Segment.
 */
void SegmentBase::reverse() {
    reversed = !reversed;
}

/**
 * Give a single LED a CRGB color.
 * @param CRGB the color to set.
 * @param int the index of the LED.
 */
void SegmentBase::setCRGB(CRGB color, int i)
{
    leds[getIndex(i)] = color;
}

/**
 * Give every LED in the Segment the same color.
 * @param CRGB color to set.
 */
void SegmentBase::setUniformCRGB(CRGB color)
{
    for (int i = 0; i < getLength(); ++i)
    {
        leds[indices[i]] = color;
    }
}