#pragma once

#include "animation.hpp"

#include "geometry/vector.hpp"

class RectHaverInterface;

class AnimationDeform : public Animation
{
public:
    AnimationDeform(int durationMs, const Vector& inFinalSize, RectHaverInterface& inTarget, bool bInShouldReset = true, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr);

    // ~Begin Animation
    virtual bool shouldReset() const override;
    virtual int getNumberOfTargets() const override { return 1; }
    virtual int getNumberOfAnimatedProperties() const override { return 2; }
    // ~End Animation

private:
    // ~Begin Animation
    virtual void setInitialValues() override;
    virtual void reinstateInitialValues() override;
    virtual void interpolate(float fraction) override;
    // ~End Animation

    const Vector finalSize;

    Vector initialSize;
    Vector difference;

    RectHaverInterface& target;
};
