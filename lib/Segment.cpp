#include "Segment.h"

template<int STRIP_LEN>
Segment<STRIP_LEN>::Segment()
{
    CRGB* array[STRIP_LEN];
}

template<int STRIP_LEN>
Segment<STRIP_LEN>::Segment(CRGB** indices[]) 
{
    CRGB* array[STRIP_LEN];

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