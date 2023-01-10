#pragma once

#include "animation.hpp"
#include "interfaces/healthHaverInterface.hpp"

class AnimationHealth : public Animation
{
public:
    AnimationHealth(int durationMs, int inFinal, HealthHaverInterface& inTarget, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr)
        : Animation(durationMs, std::move(inEasingFunction))
        , finalHealth(inFinal)
        , target(inTarget)
    {}

private:
    virtual void setInitialValues()
    {
        initialHealth = target.getHealth();
        difference = finalHealth - initialHealth;
    }
    
    virtual void reinstateInitialValues()
    {
        target.setHealth(initialHealth);
    }

    virtual void interpolate(float fraction) override
    {
        target.setHealth(initialHealth + (difference) * fraction);
    }

    const int finalHealth;

    int initialHealth;
    int difference;

    HealthHaverInterface& target;
};
