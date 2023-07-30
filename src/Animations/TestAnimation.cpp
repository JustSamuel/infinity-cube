//
// Created by Samuel on 25/03/2021.
//

#pragma once

#include "Animation.h"

void TestAnimation::draw() {
    if (step < target->getLength()) {
        target->drawGradientRange(CHSV(0, 255, 0), rgb2hsv_approximate(currentColor), 0, step + 1);
        hsv2rgb_rainbow(CHSV(animation, 200, 200), currentColor);
        step++;
    } else {
        animation = (animation + 30) % 255;
        step = 0;
        target->reverse();
        display(100, false);
    }
}