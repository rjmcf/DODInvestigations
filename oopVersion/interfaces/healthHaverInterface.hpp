#pragma once

class HealthHaverInterface
{
public:
    virtual float getHealth() const = 0;
    virtual void setHealth(float newHealth) = 0;
    virtual bool shouldAnimateHealth() const = 0;
};
