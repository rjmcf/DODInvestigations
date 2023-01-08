#pragma once

#include "animation.hpp"
#include "oopVersion/colour.hpp"
#include "oopVersion/interfaces/colourHaverInterface.hpp"

class AnimationColour : public Animation
{
public:
    AnimationColour(int durationMs, const Colour& inFinalColour, ColourHaverInterface& inTarget, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr)
        : Animation(durationMs, std::move(inEasingFunction))
        , initialColour(inTarget.getColour())
        , redDifference(inFinalColour.red - initialColour.red)
        , greenDifference(inFinalColour.green - initialColour.green)
        , blueDifference(inFinalColour.blue - initialColour.blue)
        , alphaDifference(inFinalColour.alpha - initialColour.alpha)
        , target(inTarget)
    {}

private:
    virtual void interpolate(float fraction) override
    {
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

    const Colour initialColour;
    const float redDifference;
    const float greenDifference;
    const float blueDifference;
    const float alphaDifference;

    ColourHaverInterface& target;
};
