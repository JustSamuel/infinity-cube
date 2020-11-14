//
// Created by Samuel on 13/11/2020.
//
#pragma once

#include "SegmentBase.h"

template<int STRIP_LEN>
class Segment: public SegmentBase 
{
public:
    Segment();

    Segment(CRGB**);

    void setUniformCRGB(CRGB) override;

    int getLength() override;
};
