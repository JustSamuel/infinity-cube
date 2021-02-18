//
// Created by Samuel on 16/11/2020.
//

#pragma once

#include "Animation.h"

void TestAnimation::draw() {
    target -> setUniformCRGB(CRGB::Red);
    display(5, false);
//    if (step < target->getLength()) {
//        target->drawGradientRange(CHSV(0, 255, 0), rgb2hsv_approximate(currentColor), 0, step + 1);
//        hsv2rgb_rainbow(CHSV(animation, 200, 200), currentColor);
//        display(5, false);
//        step++;
//    } else {
//        animation = (animation + 30) % 255;
//        step = 0;
//        target->reverse();
//        display(100, false);
//    }
}