//
// Created by Samuel on 16/11/2020.
//
#pragma once

#include "InfintyCube.h"

/**
 * Abstract class for describing Animations.
 */
class Animation {
protected:
// Every Animation has a Segment as target.
    SegmentBase *target;
public:

    // Construct an Animation by setting the target.
    explicit Animation(SegmentBase *target) {
        this->target = target;
    }

    // Draw is used to display the animation.
    virtual void draw() = 0;
};

/**
 * Example implementation of the Abstract Animation class.
 *
 * Pulse going from left to right, changing color on reaching the edge.
 */
class TestAnimation : public Animation {
public:
    explicit TestAnimation(SegmentBase *target) : Animation(target) {}

    void draw() override;

    bool build = true;

    int animation = 0;

    int step = 0;

    int sat = 100;

    CRGB currentColor = CRGB::Red;
};


class GitLabAnimation : public Animation {
public:
    explicit GitLabAnimation(SegmentBase *target, CRGB currentColor, int pulseCount) : Animation(target) {
        this->currentColor = currentColor;
        this->pulseCount = pulseCount;
    }

    void draw() override;

    double speed = 0.1;

    int pulseCount = 5;

    CRGB currentColor = CRGB::Red;
};


class LeapAnimation : public Animation {
public:
    explicit LeapAnimation(SegmentBase *target, CRGB currentColor, double height, double xOffset) : Animation(target) {
        this->height = height;
        this->currentColor = currentColor;
        this->xOffset = xOffset;
    }

    void draw() override;

    double height = 0;

    double xOffset = 0;

    CRGB currentColor = CRGB::Red;
};

class AlarmAnimation: public Animation {
public:
    explicit AlarmAnimation(SegmentBase *target) : Animation(target) {}

    void draw() override;

    bool build = true;

    int animation = 0;

    int step = 0;

    int sat = 100;

    CRGB currentColor = CRGB::Red;
};

class RainAnimation: public Animation {
public:
    explicit RainAnimation(SegmentBase *target) : Animation(target) {}

    void draw() override;

private:
    void dissolveRaindrops();
};