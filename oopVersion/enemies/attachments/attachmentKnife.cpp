#include "attachmentKnife.hpp"

#include "utils/drawingUtils.hpp"

AttachmentKnife::AttachmentKnife()
    : AnimatedObject(AnimatedObjectType::Knife)
{
    knifeBlade.w = 3;
    knifeBlade.h = 6;
}

void AttachmentKnife::update(int deltaTimeMs)
{
    knifeBlade.x = parent->x + offset.x;
    knifeBlade.y = parent->y + offset.y;
}
    
void AttachmentKnife::draw(std::vector<std::unique_ptr<const DrawCall>>& drawCalls)
{
    const SDL_Rect knifeBladeDrawRect = DrawingUtils::convertCentredRectToDrawRect(knifeBlade);
    drawCalls.emplace_back(std::make_unique<DrawCallFilledRect>(knifeBladeDrawRect, Colour{192, 192, 192, 255}));

    SDL_Rect handleDrawRect = knifeBladeDrawRect;
    handleDrawRect.h /= 2;
    handleDrawRect.y -= handleDrawRect.h;

    drawCalls.emplace_back(std::make_unique<DrawCallFilledRect>(handleDrawRect, Colour{102, 51, 0, 255}));

    handleDrawRect.w = handleDrawRect.h * 2;
    handleDrawRect.x -= handleDrawRect.w / 4;
    handleDrawRect.y += handleDrawRect.h / 2;
    handleDrawRect.h = knifeBladeDrawRect.w;

    drawCalls.emplace_back(std::make_unique<DrawCallFilledRect>(handleDrawRect, Colour{102, 51, 0, 255}));
}