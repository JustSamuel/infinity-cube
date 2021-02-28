//
// Created by Samuel on 16/11/2020.
//
#pragma once

#include "Animation.h"

void TestAnimation::draw() {
//    target -> setUniformCRGB(CRGB::Purple);
//    display(5, false);
    if (step < target->getLength()) {
        target->setCRGB(currentColor, step);
        hsv2rgb_rainbow(CHSV(animation, 200, 200), currentColor);
        display(5, false);
        step++;
    } else {
        animation = (animation + 30) % 255;
        step = 0;
        target->reverse();
        display(100, false);
    }
}