#pragma once

#include "animation.hpp"
#include "geometry/point.hpp"
#include "geometry/vector.hpp"
#include "interfaces/rectHaverInterface.hpp"

#include <vector>

class AnimationTranslate : public Animation
{
public:
    AnimationTranslate(int durationMs, const Vector& inDisplacement, const std::vector<RectHaverInterface*>& inTargets, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr)
        : Animation(durationMs, std::move(inEasingFunction))
        , displacement(inDisplacement)
    {
        for (RectHaverInterface* target : inTargets)
        {
            targets.emplace_back(TargetWithInitialPosition{target, Point()});
        }
    }

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
            SDL_Rect currentRect = target.target->getRect();
            currentRect.x = static_cast<int>(target.initial.x);
            currentRect.y = static_cast<int>(target.initial.y);
            target.target->setRect(currentRect);
        }
    }

    virtual void interpolate(float fraction) override
    {
        const Vector scaledDisplacement = displacement.scale(fraction);
        for (const TargetWithInitialPosition& target : targets)
        {
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
