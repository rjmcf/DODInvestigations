#pragma once

#include "animation.hpp"
#include "oopVersion/geometry/vector.hpp"
#include "oopVersion/interfaces/rectHaverInterface.hpp"

class AnimationDeform : public Animation
{
public:
    AnimationDeform(int durationMs, const Vector& inInitialSize, const Vector& inFinalSize, RectHaverInterface& inTarget, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr)
        : Animation(durationMs, std::move(inEasingFunction))
        , initialSize(inInitialSize)
        , difference(inFinalSize.add(inInitialSize.scale(-1)))
        , target(inTarget)
    {}

private:
    virtual void interpolate(float fraction) override
    {
        const Vector scaledDifference = difference.scale(fraction);
        const Vector currentSize = initialSize.add(scaledDifference);
        SDL_Rect currentRect = target.getRect();
        currentRect.w = static_cast<int>(currentSize.x);
        currentRect.h = static_cast<int>(currentSize.y);
        target.setRect(currentRect);
    }

    const Vector initialSize;
    const Vector difference;

    RectHaverInterface& target;
};
