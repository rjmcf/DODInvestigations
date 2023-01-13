#pragma once

#include "geometry/vector.hpp"

class SDL_Rect;
class SDL_Renderer;

class AttachmentBase
{
public:
    virtual void update(int deltaTimeMs) = 0;
    virtual void draw(SDL_Renderer& renderer) = 0;

    void attachTo(const SDL_Rect& inParent, const Vector& inOffset)
    {
        parent = &inParent;
        offset = inOffset;
    }
    void detach() { parent = nullptr; }

protected:
    const SDL_Rect* parent = nullptr;
    Vector offset;
};
