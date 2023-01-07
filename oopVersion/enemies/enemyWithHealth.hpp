#pragma once

#include "enemy.hpp"
#include "oopVersion/interfaces/healthHaverInterface.hpp"

class EnemyWithHealth : public Enemy, public HealthHaverInterface
{
public:
    EnemyWithHealth(int x, int y, int w, int h, const Colour& inColour, float inMaxHealth);

    // ~Begin Enemy
    virtual void draw(SDL_Renderer& renderer) override;
    // ~End Enemy

    // ~Begin HealthHaverInterface
    virtual float getHealth() const override { return currentHealth; }
    virtual void setHealth(float newHealth) override {currentHealth = newHealth;}
    // ~End HealthHaverInterface

protected:
    const float maxHealth;
    float currentHealth;
};