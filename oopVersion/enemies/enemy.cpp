#include "enemy.hpp"

Enemy::Enemy(int x, int y, int w, int h, const Colour& inColour)
    : rect{x,y, w,h}
    , colour(inColour)
{}

void Enemy::draw(SDL_Renderer& renderer)
{
    SDL_SetRenderDrawColor(&renderer, colour.red, colour.green, colour.blue, colour.alpha);
    SDL_Rect drawRect{rect.x-rect.w, rect.y-rect.h, 2*rect.w, 2*rect.h};
    SDL_RenderFillRect(&renderer, &drawRect);
    SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
}