#include "attachmentSpear.hpp"

#include "animations/animationChain.hpp"
#include "animations/animationModifyVector.hpp"
#include "utils/drawingUtils.hpp"

AttachmentSpear::AttachmentSpear()
{
    spearHead.w = 5;
    spearHead.h = 5;
}

void AttachmentSpear::update(int deltaTimeMs)
{
    spearHead.x = parent->x + offset.x;
    spearHead.y = parent->y + offset.y;
}
    
void AttachmentSpear::draw(std::vector<std::unique_ptr<const DrawCall>>& drawCalls)
{
    const SDL_Rect spearHeadDrawRect = DrawingUtils::convertCentredRectToDrawRect(spearHead);
    drawCalls.emplace_back(std::make_unique<DrawCallFilledRect>(spearHeadDrawRect, Colour{192, 192, 192, 255}));

    SDL_Rect shaftDrawRect = spearHeadDrawRect;
    shaftDrawRect.w /= 2;
    shaftDrawRect.h *= 3;
    shaftDrawRect.y -= shaftDrawRect.h;
    shaftDrawRect.x += shaftDrawRect.w / 2;

    drawCalls.emplace_back(std::make_unique<DrawCallFilledRect>(shaftDrawRect, Colour{102, 51, 0, 255}));
}

std::unique_ptr<AnimationBase> AttachmentSpear::attack()
{
    std::vector<std::unique_ptr<AnimationBase>> animations;
    
    std::unique_ptr<AnimationModifyVector> moveDown = std::make_unique<AnimationModifyVector>(100, Vector{0, 15}, *this, false);
    animations.emplace_back(std::move(moveDown));
    std::unique_ptr<AnimationModifyVector> moveUp   = std::make_unique<AnimationModifyVector>(400, Vector{0,-15}, *this, false);
    animations.emplace_back(std::move(moveUp));

    return std::make_unique<AnimationChain>(std::move(animations));
}
