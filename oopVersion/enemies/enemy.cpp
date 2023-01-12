#include "enemy.hpp"

#include "geometry/point.hpp"

#include <cmath>
#include <initializer_list>

const double Pi = 3.14159265;

Enemy::Enemy(int x, int y, int w, int h, const Colour& inColour)
    : rect{x,y, w,h}
    , colour(inColour)
{}

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
}

void Enemy::draw(SDL_Renderer& renderer) const
{
    drawBody(renderer);
    drawEye(renderer);
}

void Enemy::drawBody(SDL_Renderer& renderer) const
{
    if (bAlive)
    {
        SDL_SetRenderDrawColor(&renderer, colour.red, colour.green, colour.blue, colour.alpha);
    }
    else
    {
        SDL_SetRenderDrawColor(&renderer, 100, 150, 100, 255);
    }
    SDL_Rect drawRect = getBodyRect();
    SDL_RenderFillRect(&renderer, &drawRect);
    SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
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

void Enemy::drawEye(SDL_Renderer& renderer) const
{
    SDL_SetRenderDrawColor(&renderer, 255, 255, 255, 255);
    SDL_Rect scleraRect = getScleraRect(getBodyRect());
    SDL_RenderFillRect(&renderer, &scleraRect);

    SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);

    if (isAlive())
    {
        // Draw pupil
        SDL_Rect pupilRect = getPupilRect(scleraRect);
        pupilRect.x += pupilDisplacement.x;
        pupilRect.y += pupilDisplacement.y;
        SDL_RenderFillRect(&renderer, &pupilRect);
    }
    else
    {
        // Draw X
        Point topLeft{scleraRect.x, scleraRect.y};
        Point bottomRight{scleraRect.x + scleraRect.w, scleraRect.y + scleraRect.h};

        SDL_RenderDrawLine(&renderer, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
        SDL_RenderDrawLine(&renderer, topLeft.x, bottomRight.y, bottomRight.x, topLeft.y);
    }

    SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
}