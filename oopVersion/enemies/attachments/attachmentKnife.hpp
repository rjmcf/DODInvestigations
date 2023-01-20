#pragma once

#include "attachmentBase.hpp"

#include "animations/animationLibrary/animatedObject.hpp"
#include "interfaces/vectorHaverInterface.hpp"

#include <memory>
#include <string>

class AttachmentKnife : public AttachmentBase, public VectorHaverInterface, public AnimatedObject
{
public:
    AttachmentKnife();

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
