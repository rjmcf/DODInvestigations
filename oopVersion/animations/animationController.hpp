#pragma once

#include <memory>
#include <vector>

class AnimatedObject;
class AnimationBase;
enum class AnimationId;

class AnimationController
{
public:
    ~AnimationController();
    
    void addAnimation(std::unique_ptr<AnimationBase>&& newAnimation);
    void addAnimations(std::vector<std::unique_ptr<AnimationBase>>&& newAnimations);
    void updateAllAnimations(int deltaTimeMs);
    void pauseAllAnimations() const;
    void unpauseAllAnimations() const;

    void startAnimation(const AnimationId& id);

    void reportStatistics() const;

private:
    friend class AnimatedObject;
    void registerAnimatedObject(AnimatedObject& newAnimatedObject) { registeredAnimatedObjects.push_back(&newAnimatedObject); }

    std::vector<std::unique_ptr<AnimationBase>> allActiveAnimations;
    std::vector<std::unique_ptr<AnimationBase>> animationsPendingAdd;
    std::vector<AnimatedObject*> registeredAnimatedObjects;
    bool bUpdating = false;
};
