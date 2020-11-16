//
// Created by Samuel on 13/11/2020.
//
#pragma once

/**
 * Base class for the Segment so that arrays of Segments can be created. (see Segment.h)
 */
class SegmentBase {
        boolean reversed = false;

        virtual int getIndex(int i) = 0;

    public:
        SegmentBase() = default;

        virtual int getLength() = 0;

        virtual void setUniformCRGB(CRGB) = 0;

        virtual void reverse() = 0;

        virtual void setCRGB(CRGB, int) = 0;
};
