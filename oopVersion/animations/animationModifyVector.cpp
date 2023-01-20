#include "animationModifyVector.hpp"

#include "interfaces/vectorHaverInterface.hpp"

AnimationModifyVector::AnimationModifyVector
(
    int durationMs, 
    const Vector& inDifference, 
    VectorHaverInterface& inTarget, 
    bool bInShouldReset, 
    std::unique_ptr<EasingFunction>&& inEasingFunction
)
    : Animation(durationMs, bInShouldReset, std::move(inEasingFunction))
    , difference(inDifference)
    , target(inTarget)
{}

bool AnimationModifyVector::shouldReset() const
{ 
    return bShouldReset && target.shouldAnimateVector(); 
}

void AnimationModifyVector::setInitialValues()
{
    initialVector = target.getVector();
}

void AnimationModifyVector::reinstateInitialValues()
{
    target.setVector(initialVector);
}

void AnimationModifyVector::interpolate(float fraction)
{
    if (target.shouldAnimateVector())
    {
        target.setVector(initialVector.add(difference.scale(fraction)));
    }
}