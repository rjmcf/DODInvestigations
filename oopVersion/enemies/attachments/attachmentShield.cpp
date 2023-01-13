#include "attachmentShield.hpp"

#include "utils/drawingUtils.hpp"

AttachmentShield::AttachmentShield(const Vector& size)
{
    rect.w = size.x;
    rect.h = size.y;
}

void AttachmentShield::update(int deltaTimeMs)
{
    rect.x = parent->x + offset.x;
    rect.y = parent->y + offset.y;
}

void AttachmentShield::draw(SDL_Renderer& renderer)
{
    SDL_Rect drawRect = DrawingUtils::convertCentredRectToDrawRect(rect);
    SDL_SetRenderDrawColor(&renderer, 192, 192, 192, 255);
    SDL_RenderFillRect(&renderer, &drawRect);
    SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
}
