#pragma once

#include "animatedObjectType.hpp"
#include "utils/world.hpp"

#include <string>

class AnimatedObject
{
public:
    AnimatedObject(const AnimatedObjectType& inType)
        : type(inType)
    {
    }

    const AnimatedObjectType& getAnimatedObjectType() const { return type; }

private:
    AnimatedObjectType type;
};
