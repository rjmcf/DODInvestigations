#pragma once

#include <memory>
#include <string>

class AnimatedObject;
class AnimationBase;
enum class AnimationId;

class AnimationLibraryEntry
{
public:
    virtual std::unique_ptr<AnimationBase> getNamedAnimation(AnimatedObject& object, const AnimationId& animationId) = 0;
};

class AnimationLibraryEntry_Spear : public AnimationLibraryEntry
{
public:
    virtual std::unique_ptr<AnimationBase> getNamedAnimation(AnimatedObject& object, const AnimationId& animationId) override;
};
