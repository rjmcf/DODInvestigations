#pragma once

#include "animationBase.hpp"

#include <memory>
#include <vector>

class AnimationController
{
public:
    void addAnimation(std::unique_ptr<AnimationBase>&& newAnimation);
    void updateAllAnimations(int deltaTimeMs);
    void pauseAllAnimations() const;
    void unpauseAllAnimations() const;

    void reportStatistics() const;

private:
    std::vector<std::unique_ptr<AnimationBase>> allActiveAnimations;
    std::vector<std::unique_ptr<AnimationBase>> animationsPendingAdd;
    bool bUpdating = false;
};
