#pragma once

#include "animatedInterface.hpp"
#include "../easing/easingFunction.hpp"
#include "../events/timedEventFirer.hpp"

#include <memory>

class Animation : public AnimatedInterface, public TimedEventFirer
{
public:
    // Duration in ms
    Animation(int durationMs, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr);

    virtual void update(int deltaTimeMs) override;

    virtual int getDuration() const override { return duration; }
    virtual bool isComplete() const override { return currentTime >= duration; }

    virtual void reset() override;

private:
    // Override to capture the initial values at the start of the animation
    virtual void setInitialValues() = 0;
    // Override to force the initial values on to the target when the animation is reset
    virtual void reinstateInitialValues() = 0;
    // Abstract method, override to interpolate the actual value required
    virtual void interpolate(float fraction) = 0;

    const int duration;
    int currentTime;
    std::unique_ptr<EasingFunction> easingFunction;
};
