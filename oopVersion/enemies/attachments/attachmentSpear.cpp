#include "attachmentSpear.hpp"

#include "animations/animationChain.hpp"
#include "animations/animationTranslate.hpp"
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

