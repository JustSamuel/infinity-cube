//
// Created by Samuel on 25/03/2021.
//

#pragma once

#include "Animation.h"


void GitLabAnimation::draw() {
    // Amount of times we go from side to side
    for (int i = 0; i < pulseCount; ++i) {
        // The pulse stops when it has left the frame.
        bool hasReachedEdge = false;
        bool hasEnded = false;

        // Used for the Gaussian function.
        double index = 0;

        while (!hasEnded) {
            // To see if the pulse left the edge, we check if the last LED has been turned on.
            int average = leds[target->getIndex(target->getLength() - 1)].getAverageLight();

            if (average > 0 || hasReachedEdge) {
                hasReachedEdge = true;
                // If it has been turned on we wait till it is black again.
                if (average == 0) {
                    hasEnded = true;
                }
            }

            // Draw all the LEDs according to a gaussian function.
//            target->drawGaussian(&currentColor, 1, index, max(1, pulseCount));

            // Update using step seed.
            index = index + speed * pulseCount;
            display(2, false);
        }
        target->reverse();
    }
}