#include "animationTranslate.hpp"

#include "interfaces/rectHaverInterface.hpp"

#include <SDL.h>

AnimationTranslate::AnimationTranslate
(
    int durationMs, 
    const Vector& inDisplacement, 
    RectHaverInterface& inTarget, 
    bool bInShouldReset, 
    std::unique_ptr<EasingFunction>&& inEasingFunction
)
    : Animation(durationMs, bInShouldReset, std::move(inEasingFunction))
    , displacement(inDisplacement)
{
    targets.emplace_back(TargetWithInitialPosition{&inTarget, Point()});
}

AnimationTranslate::AnimationTranslate
(
    int durationMs, 
    const Vector& inDisplacement, 
    const std::vector<RectHaverInterface*>& inTargets, 
    bool bInShouldReset, 
    std::unique_ptr<EasingFunction>&& inEasingFunction
)
    : Animation(durationMs, bInShouldReset, std::move(inEasingFunction))
    , displacement(inDisplacement)
{
    for (RectHaverInterface* target : inTargets)
    {
        targets.emplace_back(TargetWithInitialPosition{target, Point()});
    }
}

bool AnimationTranslate::shouldReset() const 
{
    if (!bShouldReset)
    {
        return false;
    }

    for (const TargetWithInitialPosition& target : targets)
    {
        if (target.target->shouldAnimateRect())
        {
            return true;
        }
    }
    
    return false;
}

int AnimationTranslate::getNumberOfTargets() const 
{ 
    return targets.size(); 
}

void AnimationTranslate::setInitialValues()
{
    for (TargetWithInitialPosition& target : targets)
    {
        SDL_Rect currentRect = target.target->getRect();
        target.initial = Point{currentRect.x, currentRect.y};
    }
}


void AnimationTranslate::reinstateInitialValues()
{
    for (const TargetWithInitialPosition& target : targets)
    {
        if (target.target->shouldAnimateRect())
        {
            SDL_Rect currentRect = target.target->getRect();
            currentRect.x = static_cast<int>(target.initial.x);
            currentRect.y = static_cast<int>(target.initial.y);
            target.target->setRect(currentRect);
        }
    }
}

void AnimationTranslate::interpolate(float fraction)
{
    const Vector scaledDisplacement = displacement.scale(fraction);
    for (const TargetWithInitialPosition& target : targets)
    {
        if (!target.target->shouldAnimateRect())
        {
            continue;
        }

        const Point currentPosition = target.initial.translate(scaledDisplacement);
        SDL_Rect currentRect = target.target->getRect();
        currentRect.x = static_cast<int>(currentPosition.x);
        currentRect.y = static_cast<int>(currentPosition.y);
        target.target->setRect(currentRect);
    }
}
