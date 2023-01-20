#include "animationDeform.hpp"

#include "interfaces/rectHaverInterface.hpp"

#include <SDL.h>

AnimationDeform::AnimationDeform
(
    int durationMs, 
    const Vector& inFinalSize, 
    RectHaverInterface& inTarget, 
    bool bInShouldReset, 
    std::unique_ptr<EasingFunction>&& inEasingFunction
)
    : Animation(durationMs, bInShouldReset, std::move(inEasingFunction))
    , finalSize(inFinalSize)
    , target(inTarget)
{}

bool AnimationDeform::shouldReset() const
{ 
    return bShouldReset && target.shouldAnimateRect(); 
}

void AnimationDeform::setInitialValues()
{
    initialSize = Vector{float(target.getRect().w), float(target.getRect().h)};
    difference = finalSize.add(initialSize.scale(-1));
}

void AnimationDeform::reinstateInitialValues()
{
    SDL_Rect currentRect = target.getRect();
    currentRect.w = static_cast<int>(initialSize.x);
    currentRect.h = static_cast<int>(initialSize.y);
    target.setRect(currentRect);
}

void AnimationDeform::interpolate(float fraction)
{
    if (!target.shouldAnimateRect())
    {
        return;
    }

    const Vector scaledDifference = difference.scale(fraction);
    const Vector currentSize = initialSize.add(scaledDifference);
    SDL_Rect currentRect = target.getRect();
    currentRect.w = static_cast<int>(currentSize.x);
    currentRect.h = static_cast<int>(currentSize.y);
    target.setRect(currentRect);
}
