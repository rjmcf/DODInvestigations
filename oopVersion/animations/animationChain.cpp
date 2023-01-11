#include "animationChain.hpp"

AnimationChain::AnimationChain(std::vector<std::unique_ptr<Animation>>&& inAnimations)
    : animations(std::move(inAnimations))
    , numAnimations(animations.size())
{
    duration = 0;
    for (const std::unique_ptr<Animation>& animation : animations)
    {
        duration += animation->getDuration();
    }
}

void AnimationChain::update(int deltaTimeMs)
{
    if (isPaused() || isComplete())
    {
        return;
    }

    currentTimeInCurrentAnimation += deltaTimeMs;
    const std::unique_ptr<Animation>* currentAnimation = &animations[currentAnimationIndex];
    (*currentAnimation)->update(deltaTimeMs);

    if ((*currentAnimation)->isComplete())
    {
        currentTimeInCurrentAnimation -= (*currentAnimation)->getDuration();
        currentAnimationIndex++;

        if (!isComplete())
        {
            currentAnimation = &animations[currentAnimationIndex];
            (*currentAnimation)->update(currentTimeInCurrentAnimation);
            // TODO Handle the new animation being complete as well
        }
    }
}

bool AnimationChain::isComplete() const
{
    // We have moved past the last animation
    return currentAnimationIndex == numAnimations;
}

bool AnimationChain::shouldReset() const 
{
    for (const std::unique_ptr<Animation>& animation : animations)
    {
        if (!animation->shouldReset())
        {
            return false;
        }
    }

    return true;
}

void AnimationChain::reset()
{
    // Reset in reverse order so that the "final" initial position is the first one
    for (auto animation = animations.rbegin(); animation != animations.rend(); animation++)
    {
        (*animation)->reset();
    }

    currentAnimationIndex = 0;
    currentTimeInCurrentAnimation = 0;
}

int AnimationChain::getNumberOfTargets() const
{
    int totalTargets = 0;

    for (const std::unique_ptr<Animation>& animation : animations)
    {
        totalTargets += animation->getNumberOfTargets();
    }

    return totalTargets;
}

int AnimationChain::getNumberOfAnimatedProperties() const
{
    int totalProperties = 0;

    for (const std::unique_ptr<Animation>& animation : animations)
    {
        totalProperties += animation->getNumberOfAnimatedProperties();
    }

    return totalProperties;
}
