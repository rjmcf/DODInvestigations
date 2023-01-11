#pragma once

#include "animatedInterface.hpp"

#include <memory>
#include <vector>

class AnimationController
{
public:
    void addAnimation(std::unique_ptr<AnimatedInterface>&& newAnimation);
    void updateAllAnimations(int deltaTimeMs) const;
    void pauseAllAnimations() const;
    void unpauseAllAnimations() const;

private:
    std::vector<std::unique_ptr<AnimatedInterface>> allActiveAnimations;
};
