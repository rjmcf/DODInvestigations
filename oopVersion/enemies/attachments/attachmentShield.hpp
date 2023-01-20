#pragma once

#include "animations/animatedObject.hpp"
#include "attachmentBase.hpp"
#include "interfaces/rectHaverInterface.hpp"

#include <SDL.h>

class AttachmentShield : public AnimatedObject, public AttachmentBase, public RectHaverInterface
{
public:
    AttachmentShield(const Vector& size);

    // ~Begin AnimatedObject
    virtual AnimatedObjectType getAnimatedObjectType() const override;
    // ~End AnimatedObject

    // ~Begin AttachmentBase
    virtual void update(int deltaTimeMs) override;
    virtual void draw(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) override;
    // ~End AttachmentBase

    // ~Begin RectHaverInterface
    virtual const SDL_Rect& getRect() const override { return rect; };
    virtual void setRect(const SDL_Rect& inRect) override { rect = inRect; };
    virtual bool shouldAnimateRect() const override { return true; }
    // ~End RectHaverInterface

private:
    SDL_Rect rect;
};
