#include "enemyWithHealth.hpp"

EnemyWithHealth::EnemyWithHealth(int x, int y, int w, int h, const Colour& inColour, float inMaxHealth)
    : Enemy(x,y, w,h, inColour)
    , maxHealth(inMaxHealth)
    , currentHealth(inMaxHealth)
{}

void EnemyWithHealth::draw(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) const
{
    Enemy::draw(drawCalls);

    if (isAlive())
    {
        SDL_Rect healthBarRect = getBodyRect();
        healthBarRect.y -= 10;
        healthBarRect.h = 5;

        drawCalls.emplace_back(std::make_unique<DrawCallRectOutline>(healthBarRect, Colour{0, 255, 0, 255}));

        healthBarRect.w *= currentHealth / maxHealth;
        
        drawCalls.emplace_back(std::make_unique<DrawCallFilledRect>(healthBarRect, Colour{0, 255, 0, 255}));
    }
}