//
// Created by Samuel on 24/04/2021.
//

#pragma once

#include "Animation.h"

void AlarmAnimation::draw() {
    for (int i = 0; i < target->getLength(); ++i) {
        target->drawGaussian(currentColor, 1, i, 5);
        display(5, false);
    }
}