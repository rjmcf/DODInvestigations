#pragma once

#include <string>

class AnimatedObject
{
public:
    AnimatedObject(std::string&& inId)
        : id(std::move(inId))
    {}

    AnimatedObject(const std::string& inId)
        : id(inId)
    {}

    const std::string& getAnimatedObjectId() const { return id; }

private:
    std::string id;
};
