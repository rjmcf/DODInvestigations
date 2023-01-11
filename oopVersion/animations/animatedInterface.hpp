#pragma once

class AnimatedInterface
{
public:
    virtual void update(int deltaTimeMs) = 0;

    virtual int getDuration() const = 0;
    virtual bool isComplete() const = 0;

    virtual void reset() = 0;

    virtual int getNumberOfTargets() const = 0;
    virtual int getNumberOfAnimatedProperties() const = 0;

    bool isPaused() const { return bIsPaused; }
    void pause() { bIsPaused = true; }
    void unpause() { bIsPaused = false; }

private:
    bool bIsPaused = false;
};
