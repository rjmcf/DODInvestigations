#pragma once

#include "colour.hpp"
#include "oopVersion/interfaces/rectHaverInterface.hpp"

#include <SDL2/SDL.h>

class Enemy : public RectHaverInterface
{
public:
    Enemy(int x, int y, int w, int h, const Colour& inColour);

    virtual void draw(SDL_Renderer& renderer);
    virtual void update(int deltaTimeMs) {}

    // ~Begin RectHaverInterface
    virtual const SDL_Rect& getRect() const override { return rect; }
    virtual void setRect(const SDL_Rect& inRect) override { rect = inRect; }
    // ~End RectHaverInterface

protected:
    SDL_Rect rect;
    Colour colour;
};