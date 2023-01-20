#include "enemy.hpp"

#include "attachments/attachmentBase.hpp"
#include "drawCall.hpp"
#include "geometry/point.hpp"
#include "utils/drawingUtils.hpp"

#include <cmath>
#include <initializer_list>

const double Pi = 3.14159265;

Enemy::Enemy(int x, int y, int w, int h, const Colour& inColour)
    : rect{x,y, w,h}
    , colour(inColour)
{}

Enemy::~Enemy() = default;

void Enemy::attach(std::unique_ptr<AttachmentBase>&& attachment, const Vector& offset)
{
    attachment->attachTo(rect, offset);
    attachments.emplace_back(std::move(attachment));
}

void Enemy::update(int deltaTimeMs)
{
    if (!isAlive())
    {
        return;
    }

    Point mousePos;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);

    Vector toMouse = Point{rect.x, rect.y}.to(mousePos);
    toMouse.normalise();

    SDL_Rect scleraRect = getScleraRect(getBodyRect());
    SDL_Rect pupilRect = getPupilRect(scleraRect);

    float tXLeft   =  std::abs(toMouse.x) > 0.01 ? (scleraRect.x - pupilRect.x) / toMouse.x : -1;
    float tYTop    =  std::abs(toMouse.y) > 0.01 ? (scleraRect.y - pupilRect.y) / toMouse.y : -1;
    float tXRight  =  std::abs(toMouse.x) > 0.01 ? (scleraRect.x + scleraRect.w - (pupilRect.x + pupilRect.w)) / toMouse.x : -1;
    float tYBottom =  std::abs(toMouse.y) > 0.01 ? (scleraRect.y + scleraRect.h - (pupilRect.y + pupilRect.h)) / toMouse.y : -1;

    float chosenT = __FLT_MAX__;

    for (const float t : {tXLeft, tXRight, tYTop, tYBottom})
    {
        if (t < 0)
        {
            continue;
        }

        if (t < chosenT)
        {
            chosenT = t;
        }
    }

    pupilDisplacement.x = chosenT * toMouse.x;
    pupilDisplacement.y = chosenT * toMouse.y;

    for (const std::unique_ptr<AttachmentBase>& attachment : attachments)
    {
        attachment->update(deltaTimeMs);
    }
}

void Enemy::draw(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) const
{
    drawBody(drawCalls);
    drawEye(drawCalls);
    for (const std::unique_ptr<AttachmentBase>& attachment : attachments)
    {
        attachment->draw(drawCalls);
    }
}

void Enemy::drawBody(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) const
{
    drawCalls.emplace_back(std::make_unique<const DrawCallFilledRect>(getBodyRect(), bAlive ? colour : Colour{100, 150, 100, 255}));
}

SDL_Rect Enemy::getBodyRect() const 
{ 
    return DrawingUtils::convertCentredRectToDrawRect(rect); 
}

SDL_Rect Enemy::getScleraRect(const SDL_Rect& bodyRect)
{
    SDL_Rect scleraRect;
    scleraRect.x = bodyRect.x + bodyRect.w * 0.2;
    scleraRect.y = bodyRect.y + bodyRect.h * 0.2;
    scleraRect.w = bodyRect.w * 0.6;
    scleraRect.h = bodyRect.h * 0.6;

    return scleraRect;
}

SDL_Rect Enemy::getPupilRect(const SDL_Rect& scleraRect)
{
    SDL_Rect pupilRect;
    pupilRect.x = scleraRect.x + scleraRect.w * 0.25;
    pupilRect.y = scleraRect.y + scleraRect.h * 0.25;
    pupilRect.w = scleraRect.w * 0.5;
    pupilRect.h = scleraRect.h * 0.5;

    return pupilRect;
}

void Enemy::drawEye(std::vector<std::unique_ptr<const DrawCall>>& drawCalls) const
{
    const SDL_Rect scleraRect(getScleraRect(getBodyRect()));
    drawCalls.emplace_back(std::make_unique<DrawCallFilledRect>(scleraRect, Colour{255,255,255,255}));

    if (isAlive())
    {
        // Draw pupil
        SDL_Rect pupilRect = getPupilRect(scleraRect);
        pupilRect.x += pupilDisplacement.x;
        pupilRect.y += pupilDisplacement.y;
        drawCalls.emplace_back(std::make_unique<DrawCallFilledRect>(pupilRect, Colour{0,0,0,255}));
    }
    else
    {
        // Draw X
        Point topLeft{scleraRect.x, scleraRect.y};
        Point topRight{scleraRect.x + scleraRect.w, scleraRect.y};
        Point bottomLeft{scleraRect.x, scleraRect.y + scleraRect.h};
        Point bottomRight{scleraRect.x + scleraRect.w, scleraRect.y + scleraRect.h};
        drawCalls.emplace_back(std::make_unique<DrawCallLine>(topLeft, bottomRight, Colour{0,0,0,255}));
        drawCalls.emplace_back(std::make_unique<DrawCallLine>(topRight, bottomLeft, Colour{0,0,0,255}));
    }
}