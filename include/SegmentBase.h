//
// Created by Samuel on 13/11/2020.
//
#pragma once
#include "FastLED.h"
#include "Helper.h"

/**
 * Base class for the Segment so that arrays of Segments can be created. (see Segment.h)
 */
class SegmentBase {
        // If the Segment indices are reversed.
        bool reversed = false;
    public:
        // The pointers of the LEDS in the segment.
        int indices[0];

        SegmentBase() = default;

        /**
         * @returns the amount of LEDS in the segment.
         */
        virtual int getLength() = 0;

        /**
         * Sets every LED to the same color.
         * @param CRGB
         */
        void setUniformCRGB(const CRGB&);

        /**
         * Setter for the reversed boolean.
         */
        void setReversed(bool);

        void reverse();

        /**
         * Set the LED at index i to a color.
         * @param CRGB color to set.
         * @param int Index of LED.
         */
        void setCRGB(const CRGB&, int);

        /**
         * Draw a color over a range of indices.
         * @param CRGB color to set.
         * @param start start index.
         * @param length length of the range.
         * @param bool if the range should wrap around.
         */
        void drawRange(const CRGB&, int start, int length, bool = true);

        /**
         * Draw a gradient over a range of indices.
         * @param startcolor color to start with
         * @param endcolor color to end with
         * @param start start index
         * @param length length of the range
         */
        void drawGradientRange(CHSV startcolor, CHSV endcolor, int start, int length);

        int getIndex(int i);
};
