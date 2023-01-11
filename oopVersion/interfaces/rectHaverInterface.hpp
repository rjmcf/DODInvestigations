#pragma once

class SDL_Rect;

class RectHaverInterface
{
public:
    virtual const SDL_Rect& getRect() const = 0;
    virtual void setRect(const SDL_Rect& inRect) = 0;
    virtual bool shouldAnimateRect() const = 0;
};
