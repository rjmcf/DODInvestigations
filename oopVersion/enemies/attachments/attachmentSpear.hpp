#pragma once

#include "attachmentBase.hpp"

#include "animations/animationLibrary/animatedObject.hpp"
#include "interfaces/vectorHaverInterface.hpp"

#include <memory>
#include <string>

class AttachmentSpear : public AttachmentBase, public VectorHaverInterface, public AnimatedObject
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

    static std::string name;

private:
    SDL_Rect spearHead;
};
