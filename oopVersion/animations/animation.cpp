#include "animation.hpp"

#include <algorithm>
#include <SDL2/SDL.h>

Animation::Animation(int durationMs, std::unique_ptr<EasingFunction>&& inEasingFunction)
    : duration(durationMs)
    , currentTime(0)
    , easingFunction(inEasingFunction ? std::move(inEasingFunction) : std::make_unique<NoEase>())
{}

void Animation::update(int deltaTimeMs)
{
    if (bIsPaused)
    {
        return;
    }
    
    currentTime += deltaTimeMs;
    // Clamp to duration
    currentTime = std::min(currentTime, duration);

    interpolate(easingFunction->ease(currentTime / duration));
}