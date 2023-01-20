#pragma once

#include "animatedObjectType.hpp"

#include "animations/animationBase.hpp"

#include <map>
#include <memory>
#include <vector>

class AnimatedObject;
class AnimationLibraryEntry;
enum class AnimationId;

class AnimationLibrary
{
public:
    AnimationLibrary();
    ~AnimationLibrary();

    std::vector<std::unique_ptr<AnimationBase>> getAnimationsForName(AnimatedObject& object, const AnimationId& animationId);
    void startNamedAnimationFor(AnimatedObject& object, const AnimationId& animationId);

private:
    std::map<AnimatedObjectType, std::unique_ptr<AnimationLibraryEntry>> library;
};
