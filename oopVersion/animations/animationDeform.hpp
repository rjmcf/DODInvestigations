#pragma once

#include "animation.hpp"
#include "geometry/vector.hpp"
#include "interfaces/rectHaverInterface.hpp"

#include <SDL.h>

class AnimationDeform : public Animation
{
public:
    AnimationDeform(int durationMs, const Vector& inFinalSize, RectHaverInterface& inTarget, bool bInShouldReset = true, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr)
        : Animation(durationMs, bInShouldReset, std::move(inEasingFunction))
        , finalSize(inFinalSize)
        , target(inTarget)
    {}

    virtual bool shouldReset() const override { return bShouldReset && target.shouldAnimateRect(); }
    virtual int getNumberOfTargets() const override { return 1; }
    virtual int getNumberOfAnimatedProperties() const override { return 2; }

private:
    virtual void setInitialValues() override
    {
        initialSize = Vector{target.getRect().w, target.getRect().h};
        difference = finalSize.add(initialSize.scale(-1));
    }
    
    virtual void reinstateInitialValues() override
    {
        SDL_Rect currentRect = target.getRect();
        currentRect.w = static_cast<int>(initialSize.x);
        currentRect.h = static_cast<int>(initialSize.y);
        target.setRect(currentRect);
    }

    virtual void interpolate(float fraction) override
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

    const Vector finalSize;

    Vector initialSize;
    Vector difference;

    RectHaverInterface& target;
};
