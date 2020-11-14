//
// Created by Samuel on 13/11/2020.
//
#pragma once

#include "SegmentBase.h"

template<int STRIP_LEN>
class Segment: public SegmentBase 
{
public:
    CRGB* array[STRIP_LEN];

    Segment();

    Segment(CRGB* indices[]);

    void setUniformCRGB(CRGB) override;

    int getLength() override;
};

template<int STRIP_LEN>
Segment<STRIP_LEN>::Segment(CRGB* indices[])
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