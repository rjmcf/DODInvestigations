#include "animationController.hpp"

#include "Tracy.hpp"

void AnimationController::addAnimation(std::unique_ptr<AnimatedInterface>&& newAnimation)
{
    allActiveAnimations.push_back(std::move(newAnimation));
}

void AnimationController::updateAllAnimations(int deltaTimeMs) const
{
    ZoneScoped;
    for (const std::unique_ptr<AnimatedInterface>& animationPtr : allActiveAnimations)
    {
        animationPtr->update(deltaTimeMs);
        if (animationPtr->isComplete())
        {
            animationPtr->reset();
        }
    }
}
    
void AnimationController::pauseAllAnimations() const
{
    for (const std::unique_ptr<AnimatedInterface>& animationPtr : allActiveAnimations)
    {
        animationPtr->pause();
    }
}

void AnimationController::unpauseAllAnimations() const
{
    for (const std::unique_ptr<AnimatedInterface>& animationPtr : allActiveAnimations)
    {
        animationPtr->unpause();
    }
}
