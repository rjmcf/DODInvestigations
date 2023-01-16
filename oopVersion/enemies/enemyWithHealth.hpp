#pragma once

#include "enemy.hpp"
#include "interfaces/healthHaverInterface.hpp"

class EnemyWithHealth : public Enemy, public HealthHaverInterface
{
public:
    EnemyWithHealth(int x, int y, int w, int h, const Colour& inColour, float inMaxHealth);

    // ~Begin Enemy
    virtual void draw(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) const override;
    // ~End Enemy

    // ~Begin HealthHaverInterface
    virtual float getHealth() const override { return currentHealth; }
    virtual void setHealth(float newHealth) override {currentHealth = newHealth;}
    virtual bool shouldAnimateHealth() const override { return isAlive(); }
    // ~End HealthHaverInterface

protected:
    const float maxHealth;
    float currentHealth;
};