#include "animationController.hpp"

#include "profilingConfig.h"
#if PROFILING
    #include "Tracy.hpp"
    #include "TracyC.h"
#endif // PROFILING

#include <algorithm>
#include <iostream>

void AnimationController::addAnimation(std::unique_ptr<AnimationInterface>&& newAnimation)
{
    allActiveAnimations.push_back(std::move(newAnimation));
}

void AnimationController::updateAllAnimations(int deltaTimeMs)
{
#if PROFILING
    ZoneScoped;
#endif // PROFILING

    for (const std::unique_ptr<AnimationInterface>& animationPtr : allActiveAnimations) 
    {
        animationPtr->update(deltaTimeMs);
        if (animationPtr->isComplete() && animationPtr->shouldReset())
        {
            animationPtr->reset();
        }
    }

#if PROFILING
    TracyCZoneN(ctx, "Remove anims", true);
#endif // PROFILING
    // Remove all inactive animations
    int activeAnimationsBefore = allActiveAnimations.size();
    allActiveAnimations.erase(std::remove_if(allActiveAnimations.begin(), allActiveAnimations.end(), 
        [](const std::unique_ptr<AnimationInterface>& animationPtr) 
        { 
            return animationPtr->isComplete() && !animationPtr->shouldReset();
        }), allActiveAnimations.end());
    int activeAnimationsAfter = allActiveAnimations.size();
#if PROFILING
    TracyCZoneEnd(ctx);  
#endif // PROFILING

    if (activeAnimationsAfter != activeAnimationsBefore)
    {
        std::cout << "Animations before: " << activeAnimationsBefore << ", after: " << activeAnimationsAfter << "\n";
    }
}
    
void AnimationController::pauseAllAnimations() const
{
    for (const std::unique_ptr<AnimationInterface>& animationPtr : allActiveAnimations)
    {
        animationPtr->pause();
    }
}

void AnimationController::unpauseAllAnimations() const
{
    for (const std::unique_ptr<AnimationInterface>& animationPtr : allActiveAnimations)
    {
        animationPtr->unpause();
    }
}

void AnimationController::reportStatistics() const
{
    std::cout << "Animations: " << allActiveAnimations.size() << "\n";

    int totalTargets = 0;
    int totalProperties = 0;

    for (const std::unique_ptr<AnimationInterface>& animation : allActiveAnimations)
    {
        totalTargets += animation->getNumberOfTargets();
        totalProperties += animation->getNumberOfAnimatedProperties();
    }

    std::cout << "Animation Targets: " << totalTargets << "\n";
    std::cout << "Animated Properties: " << totalProperties << std::endl;
}
