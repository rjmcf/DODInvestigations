#pragma once

#include "animatedInterface.hpp"

#include <memory>
#include <vector>

class AnimationController
{
public:
    void addAnimation(std::unique_ptr<AnimatedInterface>&& newAnimation);
    void updateAllAnimations(int deltaTimeMs);
    void pauseAllAnimations() const;
    void unpauseAllAnimations() const;

    void reportStatistics() const;

private:
    std::vector<std::unique_ptr<AnimatedInterface>> allActiveAnimations;
};
