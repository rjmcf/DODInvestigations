#pragma once

#include "animation.hpp"

#include "geometry/point.hpp"
#include "geometry/vector.hpp"

#include <vector>

class RectHaverInterface;

class AnimationTranslate : public Animation
{
public:
    AnimationTranslate(int durationMs, const Vector& inDisplacement, RectHaverInterface& inTarget, bool bInShouldReset = true, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr);
    AnimationTranslate(int durationMs, const Vector& inDisplacement, const std::vector<RectHaverInterface*>& inTargets, bool bInShouldReset = true, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr);

    // ~Begin Animation
    virtual bool shouldReset() const override;
    virtual int getNumberOfTargets() const override;
    virtual int getNumberOfAnimatedProperties() const override { return 2 * getNumberOfTargets(); }
    // ~End Animation

private:
    // ~Begin Animation
    virtual void setInitialValues() override;
    virtual void reinstateInitialValues() override;
    virtual void interpolate(float fraction) override;
    // ~End Animation

    struct TargetWithInitialPosition
    {
        RectHaverInterface* target = nullptr;
        Point initial;
    };
    std::vector<TargetWithInitialPosition> targets;

    const Vector displacement;
};
