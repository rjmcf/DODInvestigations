#pragma once

#include "animationInterface.hpp"

#include <memory>
#include <vector>

class AnimationController
{
public:
    void addAnimation(std::unique_ptr<AnimationInterface>&& newAnimation);
    void updateAllAnimations(int deltaTimeMs);
    void pauseAllAnimations() const;
    void unpauseAllAnimations() const;

    void reportStatistics() const;

private:
    std::vector<std::unique_ptr<AnimationInterface>> allActiveAnimations;
};
