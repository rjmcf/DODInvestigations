#include "drawingUtils.hpp"

SDL_Rect DrawingUtils::convertCentredRectToDrawRect(const SDL_Rect& inRect)
{
    return SDL_Rect{inRect.x-inRect.w, inRect.y-inRect.h, 2*inRect.w, 2*inRect.h};
}
