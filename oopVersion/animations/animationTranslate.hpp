#pragma once

#include "animation.hpp"
#include "oopVersion/geometry/point.hpp"
#include "oopVersion/geometry/vector.hpp"
#include "oopVersion/interfaces/rectHaverInterface.hpp"

class AnimationTranslate : public Animation
{
public:
    AnimationTranslate(int durationMs, const Vector& inDisplacement, RectHaverInterface& inTarget, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr)
        : Animation(durationMs, std::move(inEasingFunction))
        , initial(Point{inTarget.getRect().x, inTarget.getRect().y})
        , displacement(inDisplacement)
        , target(inTarget)
    {}

private:
    virtual void interpolate(float fraction) override
    {
        const Vector scaledDisplacement = displacement.scale(fraction);
        const Point currentPosition = initial.translate(scaledDisplacement);
        SDL_Rect currentRect = target.getRect();
        currentRect.x = static_cast<int>(currentPosition.x);
        currentRect.y = static_cast<int>(currentPosition.y);
        target.setRect(currentRect);
    }

    const Point initial;
    const Vector displacement;

    RectHaverInterface& target;
};
