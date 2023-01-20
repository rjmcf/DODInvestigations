#include "animationColour.hpp"

#include "interfaces/colourHaverInterface.hpp"

AnimationColour::AnimationColour
(
    int durationMs, 
    const Colour& inFinalColour, 
    ColourHaverInterface& inTarget, 
    bool bInShouldReset, 
    std::unique_ptr<EasingFunction>&& inEasingFunction
)
    : Animation(durationMs, bInShouldReset, std::move(inEasingFunction))
    , finalColour(inFinalColour)
    , target(inTarget)
{}

bool AnimationColour::shouldReset() const
{ 
    return bShouldReset && target.shouldAnimateColour(); 
}

void AnimationColour::setInitialValues()
{
    initialColour = target.getColour();
    redDifference = finalColour.red - initialColour.red;
    greenDifference = finalColour.green - initialColour.green;
    blueDifference = finalColour.blue - initialColour.blue;
    alphaDifference = finalColour.alpha - initialColour.alpha;
}

void AnimationColour::reinstateInitialValues()
{
    target.setColour(initialColour);
}

void AnimationColour::interpolate(float fraction)
{
    if (!target.shouldAnimateColour())
    {
        return;
    }

    const int scaledRedDifference = static_cast<int>(redDifference * fraction);
    const int scaledGreenDifference = static_cast<int>(greenDifference * fraction);
    const int scaledBlueDifference = static_cast<int>(blueDifference * fraction);
    const int scaledAlphaDifference = static_cast<int>(alphaDifference * fraction);
    const Colour currentColour = Colour
    {
        initialColour.red + scaledRedDifference,
        initialColour.green + scaledGreenDifference,
        initialColour.blue + scaledBlueDifference,
        initialColour.alpha + scaledAlphaDifference,
    };
    target.setColour(currentColour);
}
