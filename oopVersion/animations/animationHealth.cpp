#include "animationHealth.hpp"

#include "interfaces/healthHaverInterface.hpp"

AnimationHealth::AnimationHealth
(
    int durationMs, 
    int inFinal, 
    HealthHaverInterface& inTarget, 
    bool bInShouldReset, 
    std::unique_ptr<EasingFunction>&& inEasingFunction
)
    : Animation(durationMs, bInShouldReset, std::move(inEasingFunction))
    , finalHealth(inFinal)
    , target(inTarget)
{}

bool AnimationHealth::shouldReset() const
{ 
    return bShouldReset && target.shouldAnimateHealth(); 
}

void AnimationHealth::setInitialValues()
{
    initialHealth = target.getHealth();
    difference = finalHealth - initialHealth;
}

void AnimationHealth::reinstateInitialValues()
{
    target.setHealth(initialHealth);
}

void AnimationHealth::interpolate(float fraction)
{
    if (target.shouldAnimateHealth())
    {
        target.setHealth(initialHealth + (difference) * fraction);
    }
}
