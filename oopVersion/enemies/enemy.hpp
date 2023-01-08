#pragma once

#include "oopVersion/colour.hpp"
#include "oopVersion/interfaces/colourHaverInterface.hpp"
#include "oopVersion/interfaces/rectHaverInterface.hpp"

#include <SDL2/SDL.h>

class Enemy : public RectHaverInterface, public ColourHaverInterface
{
public:
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
};