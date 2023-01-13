#pragma once

#include "attachmentBase.hpp"

#include <SDL.h>

class AttachmentShield : public AttachmentBase
{
public:
    AttachmentShield(const Vector& size);

    // ~Begin AttachmentBase
    virtual void update(int deltaTimeMs) override;
    virtual void draw(SDL_Renderer& renderer) override;
    // ~End AttachmentBase

private:
    SDL_Rect rect;
};
