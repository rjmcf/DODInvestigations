#pragma once

#include <memory>
#include <vector>

class AnimatedObject;
class AnimationBase;
enum class AnimationId;
enum class AnimatedObjectType;

class AnimationLibraryEntry
{
public:
    virtual ~AnimationLibraryEntry() = default;
    virtual std::vector<std::unique_ptr<AnimationBase>> getAnimationsForName(AnimatedObject& object, const AnimationId& animationId) = 0;

protected:
    bool checkObjectIsValid(const AnimatedObject& object);

private:
    virtual AnimatedObjectType getExpectedObjectType() const = 0; 
};

class AnimationLibraryEntry_Spear : public AnimationLibraryEntry
{
    // ~Begin AnimationLibraryEntry
public:
    virtual std::vector<std::unique_ptr<AnimationBase>> getAnimationsForName(AnimatedObject& object, const AnimationId& animationId) override;

private:
    virtual AnimatedObjectType getExpectedObjectType() const override;
    // ~End AnimationLibraryEntry
};

class AnimationLibraryEntry_Shield : public AnimationLibraryEntry
{
    // ~Begin AnimationLibraryEntry
public:
    virtual std::vector<std::unique_ptr<AnimationBase>> getAnimationsForName(AnimatedObject& object, const AnimationId& animationId) override;

private:
    virtual AnimatedObjectType getExpectedObjectType() const override;
    // ~End AnimationLibraryEntry
};

class AnimationLibraryEntry_Knife : public AnimationLibraryEntry
{
    // ~Begin AnimationLibraryEntry
public:
    virtual std::vector<std::unique_ptr<AnimationBase>> getAnimationsForName(AnimatedObject& object, const AnimationId& animationId) override;

private:
    virtual AnimatedObjectType getExpectedObjectType() const override;
    // ~End AnimationLibraryEntry
};