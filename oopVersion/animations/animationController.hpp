#pragma once

#include "animation.hpp"

#include <memory>
#include <vector>

class AnimationController
{
public:
    void addAnimation(std::unique_ptr<Animation>&& newAnimation);
    void updateAllAnimations(int deltaTimeMs);
    void pauseAllAnimations();
    void unpauseAllAnimations();

private:
    std::vector<std::unique_ptr<Animation>> allActiveAnimations;
};
