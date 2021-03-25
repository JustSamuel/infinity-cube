//
// Created by Samuel on 16/11/2020.
//

#pragma once

#include "Helper.h"
#include "SegmentBase.h"

/**
 * @return the ith index in the array of the Segment.
 */
int SegmentBase::getIndex(int i) {
    // Allows for wrapping around.
    i = i % getLength();

    // Underflow / edge cases.
    if (i < 0) {
        i = i + getLength();
    }

    if (!reversed) {
        return indices[i];
    } else {
        return indices[getLength() - i - 1];
    }
}

/**
 * Reverse the direction of the array in the Segment.
 */
void SegmentBase::reverse() {
    reversed = !reversed;
}

/**
 * Give a single LED a CRGB color.
 * @param CRGB the color to set.
 * @param int the index of the LED.
 */
void SegmentBase::setCRGB(const CRGB &color, int i) {
    leds[getIndex(i)] = color;
}

/**
 * Give every LED in the Segment the same color.
 * @param CRGB color to set.
 */
void SegmentBase::setUniformCRGB(const CRGB &color) {
    for (int i = 0; i < getLength(); ++i) {
        leds[indices[i]] = color;
    }
}

/**
 * Setter for the reversed boolean.
 * @param to the Value to set to.
 */
void SegmentBase::setReversed(bool to) {
    reversed = to;
}

void SegmentBase::drawRange(const CRGB &color, int start, int length, bool wrap) {
    if (wrap) {
        for (int i = 0; i < length; ++i) {
            setCRGB(color, start + i);
        }
    } else {
        // If not wrapping around we restrict the domain.
        if (start < 0) {
            start = start + getLength();
        }
        // Cheaper than modulo.
        for (int i = 0; i < length; ++i) {
            if (start + i < getLength()) {
                setCRGB(color, start + i);
            }
        }
    }
}

void SegmentBase::drawGradientRange(CHSV startcolor, CHSV endcolor, int start, int length) {
    // Length 1 is the same as setting a light.
    if (length == 1) {
        CRGB color = CRGB();
        hsv2rgb_rainbow(endcolor, color);
        setCRGB(color, start);
        return;
    }

    // For correct gradient in case of black
    if (endcolor.value == 0 || endcolor.saturation == 0) {
        endcolor.hue = startcolor.hue;
    }

    // Idem dito reverse.
    if (startcolor.value == 0 || startcolor.saturation == 0) {
        startcolor.hue = endcolor.hue;
    }

    for (int i = 0; i < length; ++i) {
        float frac = (float) i / (float) (length - 1);
        CRGB color = blend(startcolor, endcolor, frac * 255);
        setCRGB(color, start + i);
    }
}

/**
 * Draw the color range based on the gaussian function
 * @param a The curve peak
 * @param b The curve offset
 * @param c The variance
 */
void SegmentBase::drawGaussian(CRGB *color, double a, double b, double c) {
    CRGB temp = CRGB(*color);
    for (int i = 0; i < getLength(); ++i) {
        double factor;
        factor = getGaussianValue(i, a, b, c);

        // Multiply by factor.
        temp.r = color->r * factor;
        temp.g = color->g * factor;
        temp.b = color->b * factor;

        setCRGB(temp, i);
    }
}