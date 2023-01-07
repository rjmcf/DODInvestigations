#include "enemy.hpp"

Enemy::Enemy(int x, int y, int w, int h, const Colour& inColour)
    : rect{x,y, w,h}
    , colour(inColour)
{}

void Enemy::draw(SDL_Renderer& renderer)
{
    SDL_SetRenderDrawColor(&renderer, colour.red, colour.green, colour.blue, colour.alpha);
    SDL_RenderFillRect(&renderer, &rect);
    SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
}