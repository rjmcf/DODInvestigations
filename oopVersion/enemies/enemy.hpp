#pragma once

#include "colour.hpp"
#include "interfaces/colourHaverInterface.hpp"
#include "interfaces/rectHaverInterface.hpp"

#include "SDL.h"

class Enemy : public RectHaverInterface, public ColourHaverInterface
{
public:
    // x and y define the centre, w and h are the "radius"
    Enemy(int x, int y, int w, int h, const Colour& inColour);

    virtual void draw(SDL_Renderer& renderer);
    virtual void update(int deltaTimeMs) {}

    // ~Begin RectHaverInterface
    virtual const SDL_Rect& getRect() const override { return rect; }
    virtual void setRect(const SDL_Rect& inRect) override { rect = inRect; }
    // ~End RectHaverInterface

    // ~Begin ColourHaverInterface
    virtual const Colour& getColour() const override { return colour; }
    virtual void setColour(const Colour& newColour) override { colour = newColour; }
    // ~End ColourHaverInterface

protected:
    SDL_Rect rect;
    Colour colour;

    SDL_Rect getDrawRect() const { return SDL_Rect{rect.x-rect.w, rect.y-rect.h, 2*rect.w, 2*rect.h}; }
};