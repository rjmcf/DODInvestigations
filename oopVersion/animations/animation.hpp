#pragma once

#include "oopVersion/easing/easingFunction.hpp"
#include "oopVersion/events/timedEventFirer.hpp"

#include <memory>

class Animation : public TimedEventFirer
{
public:
    // Duration in ms
    Animation(int durationMs, std::unique_ptr<EasingFunction>&& inEasingFunction = nullptr);

    void update(int deltaTimeMs);

    bool isComplete() const { return currentTime >= duration; }

    void reset();

    void pause() { bIsPaused = true; }
    void unpause() { bIsPaused = false; }

private:
    // Abstract method, override to interpolate the actual value required
    virtual void interpolate(float fraction) = 0;

    const float duration;
    float currentTime;
    bool bIsPaused = false;
    std::unique_ptr<EasingFunction> easingFunction;
};
