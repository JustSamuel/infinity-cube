//
// Created by Samuel on 16/11/2020.
//
#pragma once
#include "InfintyCube.h"

/**
 * Abstract class for describing Animations.
 */
class Animation
{
protected:
// Every Animation has a Segment as target.
SegmentBase* target;
public:

    // Construct an Animation by setting the target.
    explicit Animation(SegmentBase* target){
        this -> target = target;
    }

    // Draw is used to display the animation.
    virtual void draw() = 0;
};

class TestAnimation: public Animation{
public:
    explicit TestAnimation(SegmentBase *target) : Animation(target) {}

    void draw() override;

    bool build = true;

    int animation = 0;

    int step = 0;

    int sat = 100;

    CRGB currentColor = CRGB::Red;
};