#include "attachmentShield.hpp"

#include "animations/animatedObjectType.hpp"
#include "drawCall.hpp"
#include "utils/drawingUtils.hpp"

AttachmentShield::AttachmentShield(const Vector& size)
{
    rect.w = size.x;
    rect.h = size.y;
}

AnimatedObjectType AttachmentShield::getAnimatedObjectType() const
{
    return AnimatedObjectType::Shield;
}

void AttachmentShield::update(int deltaTimeMs)
{
    rect.x = parent->x + offset.x;
    rect.y = parent->y + offset.y;
}

void AttachmentShield::draw(std::vector<std::unique_ptr<const DrawCall>>& drawCalls)
{
    drawCalls.emplace_back(std::make_unique<DrawCallFilledRect>(DrawingUtils::convertCentredRectToDrawRect(rect), Colour{192, 192, 192, 255}));
}
