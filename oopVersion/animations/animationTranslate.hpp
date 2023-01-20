#pragma once

#include "animation.hpp"
#include "geometry/point.hpp"
#include "geometry/vector.hpp"
#include "interfaces/rectHaverInterface.hpp"

#include <vector>

class AnimationTranslate : public Animation
{
public:
    AnimationTranslate(int durationMs, const Vector& inDisplacement, RectHaverInterface& inTarget, bool bInShouldReset = true, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr)
        : Animation(durationMs, bInShouldReset, std::move(inEasingFunction))
        , displacement(inDisplacement)
    {
        targets.emplace_back(TargetWithInitialPosition{&inTarget, Point()});
    }

    AnimationTranslate(int durationMs, const Vector& inDisplacement, const std::vector<RectHaverInterface*>& inTargets, bool bInShouldReset = true, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr)
        : Animation(durationMs, bInShouldReset, std::move(inEasingFunction))
        , displacement(inDisplacement)
    {
        for (RectHaverInterface* target : inTargets)
        {
            targets.emplace_back(TargetWithInitialPosition{target, Point()});
        }
    }

    virtual bool shouldReset() const override 
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
    virtual int getNumberOfTargets() const override { return targets.size(); }
    virtual int getNumberOfAnimatedProperties() const override { return 2 * getNumberOfTargets(); }

private:
    virtual void setInitialValues() override
    {
        for (TargetWithInitialPosition& target : targets)
        {
            SDL_Rect currentRect = target.target->getRect();
            target.initial = Point{currentRect.x, currentRect.y};
        }
    }
    
    
    virtual void reinstateInitialValues() override
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

    virtual void interpolate(float fraction) override
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

    struct TargetWithInitialPosition
    {
        RectHaverInterface* target = nullptr;
        Point initial;
    };
    std::vector<TargetWithInitialPosition> targets;

    const Vector displacement;
};
