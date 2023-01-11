#pragma once

#include "animatedInterface.hpp"
#include "animation.hpp"

#include <memory>
#include <vector>

class AnimationChain : public AnimatedInterface
{
public:
    AnimationChain(std::vector<std::unique_ptr<Animation>>&& inAnimations);

    virtual void update(int deltaTimeMs) override;

    virtual int getDuration() const override { return duration; }
    virtual bool isComplete() const override;

    virtual bool shouldReset() const override;
    virtual void reset() override;

    virtual int getNumberOfTargets() const override;
    virtual int getNumberOfAnimatedProperties() const override;

private:
    const std::vector<std::unique_ptr<Animation>> animations;
    const int numAnimations;

    int duration;
    int currentAnimationIndex = 0;
    int currentTimeInCurrentAnimation = 0;
};
