#include "animation.hpp"

#include "easing/easingFunction.hpp"

Animation::Animation(int durationMs, bool bInShouldReset, std::unique_ptr<EasingFunction>&& inEasingFunction)
    : bShouldReset(bInShouldReset)
    , duration(durationMs)
    , currentTime(0)
    , easingFunction(inEasingFunction ? std::move(inEasingFunction) : std::make_unique<NoEase>())
{}

Animation::~Animation() = default;

void Animation::update(int deltaTimeMs)
{
    if (isPaused() || isComplete())
    {
        return;
    }
    
    if (currentTime == 0)
    {
        setInitialValues();
    }

    currentTime += deltaTimeMs;
    // Clamp to duration
    currentTime = std::min(currentTime, duration);

    interpolate(easingFunction->ease(currentTime / (float)duration));
    fireEventsForTime(currentTime);
}

void Animation::reset()
{ 
    currentTime = 0; 
    reinstateInitialValues();
    resetAllEvents(); 
}
