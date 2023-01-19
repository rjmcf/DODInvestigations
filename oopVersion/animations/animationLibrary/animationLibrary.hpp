#pragma once

#include <map>
#include <memory>
#include <string>

class AnimatedObject;
class AnimationBase;
class AnimationLibraryEntry;

class AnimationLibrary
{
public:
    static void initialise();
    static std::unique_ptr<AnimationBase> getNamedAnimationFor(AnimatedObject& object, const std::string& animName);
    static void startNamedAnimationFor(AnimatedObject& object, const std::string& animName);

    static std::string attackAnimName;

private:
    static std::map<std::string, std::unique_ptr<AnimationLibraryEntry>> library;
};
