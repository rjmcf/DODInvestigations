#pragma once

class Animation
{
public:
    // Duration in ms
    Animation(int durationMs);

    void update(int deltaTimeMs);

    bool isComplete() const { return currentTime >= duration; }

    void reset() { currentTime = 0; }

    void pause() { bIsPaused = true; }
    void unpause() { bIsPaused = false; }

private:
    // Abstract method, override to interpolate the actual value required
    virtual void interpolate(float fraction) = 0;

    const float duration;
    float currentTime;
    bool bIsPaused = false;
};
