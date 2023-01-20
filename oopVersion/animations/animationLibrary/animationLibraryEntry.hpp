#pragma once

#include <memory>
#include <string>
#include <vector>

class AnimatedObject;
class AnimationBase;
enum class AnimationId;
enum class AnimatedObjectType;

class AnimationLibraryEntry
{
public:
    virtual std::vector<std::unique_ptr<AnimationBase>> getAnimationsForName(AnimatedObject& object, const AnimationId& animationId) = 0;

protected:
    bool checkObjectIsValid(const AnimatedObject& object);

private:
    virtual AnimatedObjectType getExpectedObjectType() const = 0; 
};

class AnimationLibraryEntry_Spear : public AnimationLibraryEntry
{
public:
    virtual std::vector<std::unique_ptr<AnimationBase>> getAnimationsForName(AnimatedObject& object, const AnimationId& animationId) override;

private:
    virtual AnimatedObjectType getExpectedObjectType() const override;
};

class AnimationLibraryEntry_Shield : public AnimationLibraryEntry
{
public:
    virtual std::vector<std::unique_ptr<AnimationBase>> getAnimationsForName(AnimatedObject& object, const AnimationId& animationId) override;

private:
    virtual AnimatedObjectType getExpectedObjectType() const override;
};
