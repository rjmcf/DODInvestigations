#pragma once

#include <SDL2/SDL.h>

class RectHaverInterface
{
public:
    virtual const SDL_Rect& getRect() const = 0;
    virtual void setRect(const SDL_Rect& inRect) = 0;
};
