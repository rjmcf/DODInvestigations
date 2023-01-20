#pragma once

#include "animation.hpp"

class HealthHaverInterface;

class AnimationHealth : public Animation
{
public:
    AnimationHealth(int durationMs, int inFinal, HealthHaverInterface& inTarget, bool bInShouldReset = true, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr);

    // ~Begin Animation
    virtual bool shouldReset() const override;
    virtual int getNumberOfTargets() const override { return 1; }
    virtual int getNumberOfAnimatedProperties() const override { return 1; }
    // ~End Animation

private:
    // ~Begin Animation
    virtual void setInitialValues() override;
    virtual void reinstateInitialValues() override;
    virtual void interpolate(float fraction) override;
    // ~End Animation

    const int finalHealth;

    int initialHealth;
    int difference;

    HealthHaverInterface& target;
};
