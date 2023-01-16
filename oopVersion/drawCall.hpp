#pragma once

#include "colour.hpp"
#include "geometry/point.hpp"

#include <SDL.h>

class DrawCall
{
public:
    DrawCall(const Colour& inColour)
        : colour(inColour)
    {}

    virtual void draw(SDL_Renderer& renderer) const = 0;

protected:
    const Colour colour;
};

class DrawCallBackground : public DrawCall
{
public:
    DrawCallBackground(const Colour& inColour)
        : DrawCall(inColour)
    {}

    virtual void draw(SDL_Renderer& renderer) const override
    {
        SDL_SetRenderDrawColor(&renderer, colour.red, colour.green, colour.blue, colour.alpha);
        SDL_RenderFillRect(&renderer, nullptr);
    }
};

class DrawCallFilledRect : public DrawCall
{
public:
    DrawCallFilledRect(const SDL_Rect& inRect, const Colour& inColour)
        : DrawCall(inColour)
        , rect(inRect)
    {}

    virtual void draw(SDL_Renderer& renderer) const override
    {
        SDL_SetRenderDrawColor(&renderer, colour.red, colour.green, colour.blue, colour.alpha);
        SDL_RenderFillRect(&renderer, &rect);
    }

private:
    const SDL_Rect rect;
};

class DrawCallRectOutline : public DrawCall
{
public:
    DrawCallRectOutline(const SDL_Rect& inRect, const Colour& inColour)
        : DrawCall(inColour)
        , rect(inRect)
    {}

    virtual void draw(SDL_Renderer& renderer) const override
    {
        SDL_SetRenderDrawColor(&renderer, colour.red, colour.green, colour.blue, colour.alpha);
        SDL_RenderDrawRect(&renderer, &rect);
    }

private:
    const SDL_Rect rect;
};

class DrawCallLine : public DrawCall
{
public:
    DrawCallLine(const Point& inFrom, const Point& inTo, const Colour& inColour)
        : DrawCall(inColour)
        , from(inFrom)
        , to(inTo)
    {}

    virtual void draw(SDL_Renderer& renderer) const override
    {
        SDL_SetRenderDrawColor(&renderer, colour.red, colour.green, colour.blue, colour.alpha);
        SDL_RenderDrawLine(&renderer, from.x, from.y, to.x, to.y);
    }

private:
    const Point from;
    const Point to;
};
