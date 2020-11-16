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
        bool reversed = false;
    public:
        int indices[];

        SegmentBase() = default;

        virtual int getLength() = 0;

        void setUniformCRGB(CRGB);

        void reverse();

        void setCRGB(CRGB, int);

        int getIndex(int i);
};
