#pragma once

#include "attachmentBase.hpp"

#include "animations/animationBase.hpp"

#include <memory>

class AttachmentSpear : public AttachmentBase
{
public:
    AttachmentSpear();

    virtual void update(int deltaTimeMs) override;
    virtual void draw(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) override;

private:
    SDL_Rect spearHead;
};
