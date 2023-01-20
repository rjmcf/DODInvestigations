#pragma once

#include "geometry/vector.hpp"

#include <memory>
#include <vector>

class DrawCall;
class SDL_Rect;

class AttachmentBase
{
public:
    virtual ~AttachmentBase() = default;
    virtual void update(int deltaTimeMs) = 0;
    virtual void draw(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) = 0;

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
