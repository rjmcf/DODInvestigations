#pragma once

#include "animation.hpp"
#include "geometry/vector.hpp"
#include "interfaces/vectorHaverInterface.hpp"

class AnimationModifyVector : public Animation
{
public:
    AnimationModifyVector(int durationMs, const Vector& inFinal, VectorHaverInterface& inTarget, bool bInShouldReset = true, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr)
        : Animation(durationMs, bInShouldReset, std::move(inEasingFunction))
        , finalVector(inFinal)
        , target(inTarget)
    {}

    virtual bool shouldReset() const override { return bShouldReset && target.shouldAnimateVector(); }
    virtual int getNumberOfTargets() const override { return 1; }
    virtual int getNumberOfAnimatedProperties() const override { return 2; }

private:
    virtual void setInitialValues()
    {
        initialVector = target.getVector();
        difference = finalVector.add(initialVector.scale(-1));
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

    const Vector finalVector;

    Vector initialVector;
    Vector difference;

    VectorHaverInterface& target;
};
