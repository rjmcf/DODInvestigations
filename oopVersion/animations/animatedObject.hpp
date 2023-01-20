#pragma once

enum class AnimatedObjectType;

class AnimatedObject
{
public:
    AnimatedObject();
    virtual ~AnimatedObject() = default;
    virtual AnimatedObjectType getAnimatedObjectType() const = 0;
};
