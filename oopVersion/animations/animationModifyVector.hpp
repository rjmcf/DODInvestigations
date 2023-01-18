#pragma once

#include "animation.hpp"
#include "geometry/vector.hpp"
#include "interfaces/vectorHaverInterface.hpp"

class AnimationModifyVector : public Animation
{
public:
    AnimationModifyVector(int durationMs, const Vector& inDifference, VectorHaverInterface& inTarget, bool bInShouldReset = true, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr)
        : Animation(durationMs, bInShouldReset, std::move(inEasingFunction))
        , difference(inDifference)
        , target(inTarget)
    {}

    virtual bool shouldReset() const override { return bShouldReset && target.shouldAnimateVector(); }
    virtual int getNumberOfTargets() const override { return 1; }
    virtual int getNumberOfAnimatedProperties() const override { return 2; }

private:
    virtual void setInitialValues()
    {
        initialVector = target.getVector();
    }
    
    virtual void reinstateInitialValues()
    {
        target.setVector(initialVector);
    }

    virtual void interpolate(float fraction) override
    {
        if (target.shouldAnimateVector())
        {
            target.setVector(initialVector.add(difference.scale(fraction)));
        }
    }

    const Vector difference;

    Vector initialVector;

    VectorHaverInterface& target;
};
