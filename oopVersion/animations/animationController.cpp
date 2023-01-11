#include "animationController.hpp"

#include "Tracy.hpp"

#include <iostream>

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

void AnimationController::reportStatistics() const
{
    std::cout << "Animations: " << allActiveAnimations.size() << "\n";

    int totalTargets = 0;
    int totalProperties = 0;

    for (const std::unique_ptr<AnimatedInterface>& animation : allActiveAnimations)
    {
        totalTargets += animation->getNumberOfTargets();
        totalProperties += animation->getNumberOfAnimatedProperties();
    }

    std::cout << "Animation Targets: " << totalTargets << "\n";
    std::cout << "Animated Properties: " << totalProperties << std::endl;
}
