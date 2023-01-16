#pragma once

#include "attachmentBase.hpp"
#include "drawCall.hpp"

#include <SDL.h>
#include <vector>

class AttachmentShield : public AttachmentBase
{
public:
    AttachmentShield(const Vector& size);

    // ~Begin AttachmentBase
    virtual void update(int deltaTimeMs) override;
    virtual void draw(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) override;
    // ~End AttachmentBase

private:
    SDL_Rect rect;
};
