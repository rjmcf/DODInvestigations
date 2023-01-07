#pragma once

#include "colour.hpp"

#include <SDL2/SDL.h>

class Enemy
{
public:
    Enemy(int x, int y, int w, int h, const Colour& inColour);

    virtual void draw(SDL_Renderer& renderer);
    virtual void update(int deltaTimeMs) {}

protected:
    SDL_Rect rect;
    Colour colour;
};