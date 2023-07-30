//
// Created by Samuel on 30/07/2023.
//

#pragma once

#include "Animation.h"

void RainAnimation::draw() {
    // Pick a random index to simulate a raindrop falling
    int raindropIndex = random(target->getLength());
    // Set the raindrop at the selected index to blue color
    target->setCRGB(CRGB(255, 85, 0), raindropIndex);

    dissolveRaindrops();
}

void RainAnimation::dissolveRaindrops() {
    for (int i = 0; i < target->getLength(); i++) {
        // Get the current color of the LED
        CRGB color = target->getCRGB(i);
        // Gradually reduce the brightness of the LED color
        color.nscale8_video(230); // Adjust the scale value to control the dissolving speed
        // Set the updated color back to the LED
        target->setCRGB(color, i);
    }
    // Display the updated LED strip
    display(5, false);
}