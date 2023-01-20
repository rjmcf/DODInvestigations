#pragma once

#include "animation.hpp"

#include "geometry/vector.hpp"

class VectorHaverInterface;

class AnimationModifyVector : public Animation
{
public:
    AnimationModifyVector(int durationMs, const Vector& inDifference, VectorHaverInterface& inTarget, bool bInShouldReset = true, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr);

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

    const Vector difference;

    Vector initialVector;

    VectorHaverInterface& target;
};
