#include "animationController.hpp"

void AnimationController::addAnimation(std::unique_ptr<AnimatedInterface>&& newAnimation)
{
    allActiveAnimations.push_back(std::move(newAnimation));
}

void AnimationController::updateAllAnimations(int deltaTimeMs)
{
    for (const std::unique_ptr<AnimatedInterface>& animationPtr : allActiveAnimations)
    {
        animationPtr->update(deltaTimeMs);
        if (animationPtr->isComplete())
        {
            animationPtr->reset();
        }
    }
}
    
void AnimationController::pauseAllAnimations()
{
    for (const std::unique_ptr<AnimatedInterface>& animationPtr : allActiveAnimations)
    {
        animationPtr->pause();
    }
}

void AnimationController::unpauseAllAnimations()
{
    for (const std::unique_ptr<AnimatedInterface>& animationPtr : allActiveAnimations)
    {
        animationPtr->unpause();
    }
}
