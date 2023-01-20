#pragma once

#include "animation.hpp"

#include "colour.hpp"

class ColourHaverInterface;

class AnimationColour : public Animation
{
public:
    AnimationColour(int durationMs, const Colour& inFinalColour, ColourHaverInterface& inTarget, bool bInShouldReset = true, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr);

    // ~Begin Animation
    virtual bool shouldReset() const override;
    virtual int getNumberOfTargets() const override { return 1; }
    virtual int getNumberOfAnimatedProperties() const override { return 4; }
    // ~End Animation

private:
    // ~Begin Animation
    virtual void setInitialValues() override;
    virtual void reinstateInitialValues() override;
    virtual void interpolate(float fraction) override;
    // ~End Animation

    Colour initialColour;
    const Colour finalColour;
    float redDifference;
    float greenDifference;
    float blueDifference;
    float alphaDifference;

    ColourHaverInterface& target;
};
