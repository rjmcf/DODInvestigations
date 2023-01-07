#include "animation.hpp"

#include <algorithm>
#include <SDL2/SDL.h>

Animation::Animation(int durationMs)
    : duration(durationMs)
    , currentTime(0)
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

    interpolate(currentTime / duration);
}