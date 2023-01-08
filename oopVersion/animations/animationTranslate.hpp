#pragma once

#include "animation.hpp"
#include "oopVersion/geometry/point.hpp"
#include "oopVersion/interfaces/rectHaverInterface.hpp"

class AnimationTranslate : public Animation
{
public:
    AnimationTranslate(int durationMs, const Point& inInitial, const Point& inFinal, RectHaverInterface& inTarget, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr)
        : Animation(durationMs, std::move(inEasingFunction))
        , initial(inInitial)
        , difference(inInitial.to(inFinal))
        , target(inTarget)
    {}

private:
    virtual void interpolate(float fraction) override
    {
        const Vector scaledDifference = difference.scale(fraction);
        const Point currentPosition = initial.translate(scaledDifference);
        SDL_Rect currentRect = target.getRect();
        currentRect.x = static_cast<int>(currentPosition.x);
        currentRect.y = static_cast<int>(currentPosition.y);
        target.setRect(currentRect);
    }

    const Point initial;
    const Vector difference;

    RectHaverInterface& target;
};
