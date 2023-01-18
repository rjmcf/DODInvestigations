#pragma once

#include "attachmentBase.hpp"

#include "animations/animationBase.hpp"
#include "interfaces/vectorHaverInterface.hpp"

#include <memory>

class AttachmentSpear : public AttachmentBase, public VectorHaverInterface
{
public:
    AttachmentSpear();

    // ~Begin AttachmentBase
    virtual void update(int deltaTimeMs) override;
    virtual void draw(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) override;
    // ~End AttachmentBase

    // ~Begin VectorHaverInterface
    virtual const Vector& getVector() const override { return offset; }
    virtual void setVector(const Vector& inVector) override { offset = inVector; }
    virtual bool shouldAnimateVector() const override { return true; }
    // ~End VectorHaverInterface

    std::unique_ptr<AnimationBase> attack();

private:
    SDL_Rect spearHead;
};
