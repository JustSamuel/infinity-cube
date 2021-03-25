//
// Created by Samuel on 25/03/2021.
//


#pragma once

#include "Animation.h"

void LeapAnimation::draw() {
    target->drawGaussian(&currentColor, 1, LeapAnimation::target->getLength()*xOffset, height);
}