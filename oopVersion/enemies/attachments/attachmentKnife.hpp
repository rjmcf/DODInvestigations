#pragma once

#include "animations/animatedObject.hpp"
#include "attachmentBase.hpp"
#include "interfaces/vectorHaverInterface.hpp"

#include <SDL.h>

class AttachmentKnife : public AnimatedObject, public AttachmentBase, public VectorHaverInterface
{
public:
    AttachmentKnife();

    // ~Begin AnimatedObject
    virtual AnimatedObjectType getAnimatedObjectType() const override;
    // ~End AnimatedObject

    // ~Begin AttachmentBase
    virtual void update(int deltaTimeMs) override;
    virtual void draw(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) override;
    // ~End AttachmentBase

    // ~Begin VectorHaverInterface
    virtual const Vector& getVector() const override { return offset; }
    virtual void setVector(const Vector& inVector) override { offset = inVector; }
    virtual bool shouldAnimateVector() const override { return true; }
    // ~End VectorHaverInterface

private:
    SDL_Rect knifeBlade;
};
