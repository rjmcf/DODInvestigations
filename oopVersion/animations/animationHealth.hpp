#pragma once

#include "animation.hpp"
#include "interfaces/healthHaverInterface.hpp"

class AnimationHealth : public Animation
{
public:
    AnimationHealth(int durationMs, int inFinal, HealthHaverInterface& inTarget, bool bInShouldReset = true, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr)
        : Animation(durationMs, bInShouldReset, std::move(inEasingFunction))
        , finalHealth(inFinal)
        , target(inTarget)
    {}

    virtual bool shouldReset() const override { return bShouldReset && target.shouldAnimateHealth(); }
    virtual int getNumberOfTargets() const override { return 1; }
    virtual int getNumberOfAnimatedProperties() const override { return 1; }

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
        if (target.shouldAnimateHealth())
        {
            target.setHealth(initialHealth + (difference) * fraction);
        }
    }

    const int finalHealth;

    int initialHealth;
    int difference;

    HealthHaverInterface& target;
};
