//
// Created by Samuel on 13/11/2020.
//
#pragma once

/**
 * Base class for the Segment so that Segment arrays can be created.
 */
class SegmentBase {
    public:
        SegmentBase();

        virtual int getLength();

        virtual void setUniformCRGB(CRGB);
};
