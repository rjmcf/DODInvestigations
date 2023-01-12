#pragma once

#include "colour.hpp"
#include "interfaces/colourHaverInterface.hpp"
#include "interfaces/rectHaverInterface.hpp"
#include "geometry/vector.hpp"

#include <SDL.h>

class Enemy : public RectHaverInterface, public ColourHaverInterface
{
public:
    // x and y define the centre, w and h are the "radius"
    Enemy(int x, int y, int w, int h, const Colour& inColour, bool bInHidden);

    virtual void update(int deltaTimeMs);
    virtual void draw(SDL_Renderer& renderer) const;

    // ~Begin RectHaverInterface
    virtual const SDL_Rect& getRect() const override { return rect; }
    virtual void setRect(const SDL_Rect& inRect) override { rect = inRect; }
    virtual bool shouldAnimateRect() const override { return isAlive(); }
    // ~End RectHaverInterface

    // ~Begin ColourHaverInterface
    virtual const Colour& getColour() const override { return colour; }
    virtual void setColour(const Colour& newColour) override { colour = newColour; }
    virtual bool shouldAnimateColour() const override { return isAlive(); }
    // ~End ColourHaverInterface

    bool isAlive() const { return bAlive; }
    void kill() { bAlive = false; }

protected:
    SDL_Rect rect;
    Colour colour;

    SDL_Rect getBodyRect() const { return SDL_Rect{rect.x-rect.w, rect.y-rect.h, 2*rect.w, 2*rect.h}; }
    static SDL_Rect getScleraRect(const SDL_Rect& bodyRect);
    static SDL_Rect getPupilRect(const SDL_Rect& scleraRect);

    void drawBody(SDL_Renderer& renderer) const;
    void drawEye(SDL_Renderer& renderer) const;

    bool isHidden() const { return bHidden; }

private:
    bool bAlive = true;
    Vector pupilDisplacement;
    bool bHidden = false;
};