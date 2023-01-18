#include "animationController.hpp"

#include "programConfig.h"
#if PROFILING
    #include "Tracy.hpp"
    #include "TracyC.h"
#endif // PROFILING

#include <algorithm>
#include <iostream>

void AnimationController::addAnimation(std::unique_ptr<AnimationBase>&& newAnimation)
{
    if (bUpdating)
    {
        animationsPendingAdd.emplace_back(std::move(newAnimation));
    }
    else
    {
        allActiveAnimations.emplace_back(std::move(newAnimation));
    }
}

void AnimationController::updateAllAnimations(int deltaTimeMs)
{
#if PROFILING
    ZoneScoped;
#endif // PROFILING

    bUpdating = true;
    for (const std::unique_ptr<AnimationBase>& animationPtr : allActiveAnimations) 
    {
        animationPtr->update(deltaTimeMs);
        if (animationPtr->isComplete() && animationPtr->shouldReset())
        {
            animationPtr->reset();
        }
    }
    bUpdating = false;

    // Add all animations pending add
    for (std::unique_ptr<AnimationBase>& animationPtr : animationsPendingAdd) 
    {
        allActiveAnimations.emplace_back(std::move(animationPtr));
    }
    animationsPendingAdd.clear();

#if PROFILING
    TracyCZoneN(ctx, "Remove anims", true);
#endif // PROFILING
    // Remove all inactive animations
    allActiveAnimations.erase(std::remove_if(allActiveAnimations.begin(), allActiveAnimations.end(), 
        [](const std::unique_ptr<AnimationBase>& animationPtr) 
        { 
            return animationPtr->isComplete() && !animationPtr->shouldReset();
        }), allActiveAnimations.end());
#if PROFILING
    TracyCZoneEnd(ctx);  
#endif // PROFILING
}
    
void AnimationController::pauseAllAnimations() const
{
    for (const std::unique_ptr<AnimationBase>& animationPtr : allActiveAnimations)
    {
        animationPtr->pause();
    }
}

void AnimationController::unpauseAllAnimations() const
{
    for (const std::unique_ptr<AnimationBase>& animationPtr : allActiveAnimations)
    {
        animationPtr->unpause();
    }
}

void AnimationController::reportStatistics() const
{
    std::cout << "Animations: " << allActiveAnimations.size() << "\n";

    int totalTargets = 0;
    int totalProperties = 0;

    for (const std::unique_ptr<AnimationBase>& animation : allActiveAnimations)
    {
        totalTargets += animation->getNumberOfTargets();
        totalProperties += animation->getNumberOfAnimatedProperties();
    }

    std::cout << "Animation Targets: " << totalTargets << "\n";
    std::cout << "Animated Properties: " << totalProperties << std::endl;
}
