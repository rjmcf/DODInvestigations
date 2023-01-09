#pragma once

#include "animatedInterface.hpp"

#include <memory>
#include <vector>

class AnimationController
{
public:
    void addAnimation(std::unique_ptr<AnimatedInterface>&& newAnimation);
    void updateAllAnimations(int deltaTimeMs);
    void pauseAllAnimations();
    void unpauseAllAnimations();

private:
    std::vector<std::unique_ptr<AnimatedInterface>> allActiveAnimations;
};
