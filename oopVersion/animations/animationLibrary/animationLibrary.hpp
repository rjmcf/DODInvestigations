#pragma once

#include "animatedObjectType.hpp"
#include "animationLibraryEntry.hpp"

#include <map>
#include <memory>
#include <string>

class AnimatedObject;
class AnimationBase;
enum class AnimationId;

class AnimationLibrary
{
public:
    AnimationLibrary();

    std::unique_ptr<AnimationBase> getNamedAnimationFor(AnimatedObject& object, const AnimationId& animationId);
    void startNamedAnimationFor(AnimatedObject& object, const AnimationId& animationId);

private:
    std::map<AnimatedObjectType, std::unique_ptr<AnimationLibraryEntry>> library;
};
