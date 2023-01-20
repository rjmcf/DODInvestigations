#pragma once

#include "animationBase.hpp"

#include <memory>
#include <vector>

class AnimationChain : public AnimationBase
{
public:
    AnimationChain(std::vector<std::unique_ptr<AnimationBase>>&& inAnimations);

    // ~Begin AnimationBase
    virtual void update(int deltaTimeMs) override;
    virtual int getDuration() const override { return duration; }
    virtual bool isComplete() const override;
    virtual bool shouldReset() const override;
    virtual void reset() override;
    virtual int getNumberOfTargets() const override;
    virtual int getNumberOfAnimatedProperties() const override;
    // ~Begin AnimationBase

private:
    const std::vector<std::unique_ptr<AnimationBase>> animations;
    const int numAnimations;

    int duration;
    int currentAnimationIndex = 0;
    int currentTimeInCurrentAnimation = 0;
};
