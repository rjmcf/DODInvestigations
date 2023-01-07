#pragma once

#include "animation.hpp"
#include "oopVersion/interfaces/healthHaverInterface.hpp"

class AnimationHealth : public Animation
{
public:
    AnimationHealth(int durationMs, int inInitial, int inFinal, HealthHaverInterface& inTarget)
        : Animation(durationMs)
        , initial(inInitial)
        , difference(inFinal - inInitial)
        , target(inTarget)
    {}

private:
    virtual void interpolate(float fraction) override
    {
        target.setHealth(initial + (difference) * fraction);
    }

    const int initial;
    const int difference;

    HealthHaverInterface& target;
};
