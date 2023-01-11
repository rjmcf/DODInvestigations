#include "enemy.hpp"

Enemy::Enemy(int x, int y, int w, int h, const Colour& inColour)
    : rect{x,y, w,h}
    , colour(inColour)
{}

void Enemy::draw(SDL_Renderer& renderer) const
{
    if (bAlive)
    {
        SDL_SetRenderDrawColor(&renderer, colour.red, colour.green, colour.blue, colour.alpha);
    }
    else
    {
        SDL_SetRenderDrawColor(&renderer, 100, 150, 100, 255);
    }
    SDL_Rect drawRect = getDrawRect();
    SDL_RenderFillRect(&renderer, &drawRect);
    SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
}