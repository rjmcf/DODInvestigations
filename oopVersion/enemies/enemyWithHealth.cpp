#include "enemyWithHealth.hpp"

EnemyWithHealth::EnemyWithHealth(int x, int y, int w, int h, const Colour& inColour, float inMaxHealth, bool bInHidden)
    : Enemy(x,y, w,h, inColour, bInHidden)
    , maxHealth(inMaxHealth)
    , currentHealth(inMaxHealth)
{}

void EnemyWithHealth::draw(SDL_Renderer& renderer) const
{
    Enemy::draw(renderer);

    if (isAlive())
    {
        SDL_Rect healthBarRect = getBodyRect();
        healthBarRect.y -= 10;
        healthBarRect.h = 5;

        SDL_SetRenderDrawColor(&renderer, 0, 255, 0, colour.alpha);

        if (!isHidden())
        {
            SDL_RenderDrawRect(&renderer, &healthBarRect);
        }

        healthBarRect.w *= currentHealth / maxHealth;

        if (!isHidden())
        {
            SDL_RenderFillRect(&renderer, &healthBarRect);
        }

        SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
    }
}