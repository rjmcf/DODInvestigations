#pragma once

#include "animation.hpp"
#include "colour.hpp"
#include "interfaces/colourHaverInterface.hpp"

class AnimationColour : public Animation
{
public:
    AnimationColour(int durationMs, const Colour& inFinalColour, ColourHaverInterface& inTarget, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr)
        : Animation(durationMs, std::move(inEasingFunction))
        , finalColour(inFinalColour)
        , target(inTarget)
    {}

    virtual int getNumberOfTargets() const override { return 1; }
    virtual int getNumberOfAnimatedProperties() const override { return 4; }

private:
    virtual void setInitialValues() override
    {
        initialColour = target.getColour();
        redDifference = finalColour.red - initialColour.red;
        greenDifference = finalColour.green - initialColour.green;
        blueDifference = finalColour.blue - initialColour.blue;
        alphaDifference = finalColour.alpha - initialColour.alpha;
    }

    virtual void reinstateInitialValues() override
    {
        target.setColour(initialColour);
    }

    virtual void interpolate(float fraction) override
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

    Colour initialColour;
    const Colour finalColour;
    float redDifference;
    float greenDifference;
    float blueDifference;
    float alphaDifference;

    ColourHaverInterface& target;
};
