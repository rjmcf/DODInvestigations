#pragma once

#include "animatedObjectType.hpp"
#include "animations/animationController.hpp"
#include "utils/world.hpp"

#include <string>

class AnimatedObject
{
public:
    AnimatedObject(const AnimatedObjectType& inType)
        : type(inType)
    {
        World::getAnimationController().registerAnimatedObject(*this);
    }

    const AnimatedObjectType& getAnimatedObjectType() const { return type; }

private:
    AnimatedObjectType type;
};
