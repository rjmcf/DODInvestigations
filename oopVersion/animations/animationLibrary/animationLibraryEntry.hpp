#pragma once

#include <memory>
#include <string>

class AnimatedObject;
class AnimationBase;

class AnimationLibraryEntry
{
public:
    virtual std::unique_ptr<AnimationBase> getNamedAnimation(AnimatedObject& object, const std::string& animName) = 0;
};

class AnimationLibraryEntry_Spear : public AnimationLibraryEntry
{
public:
    virtual std::unique_ptr<AnimationBase> getNamedAnimation(AnimatedObject& object, const std::string& animName) override;
};
