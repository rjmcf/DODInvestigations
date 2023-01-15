#pragma once

#include "attachments/attachmentBase.hpp"
#include "colour.hpp"
#include "interfaces/colourHaverInterface.hpp"
#include "interfaces/rectHaverInterface.hpp"
#include "geometry/vector.hpp"
#include "utils/drawingUtils.hpp"

#include <SDL.h>

#include <vector>
#include <memory>

class Enemy : public RectHaverInterface, public ColourHaverInterface
{
public:
    // x and y define the centre, w and h are the "radius"
    Enemy(int x, int y, int w, int h, const Colour& inColour);

    virtual void update(int deltaTimeMs);
    virtual void draw(SDL_Renderer& renderer) const;

    // ~Begin RectHaverInterface
    virtual const SDL_Rect& getRect() const override { return rect; }
    virtual void setRect(const SDL_Rect& inRect) override { rect = inRect; }
    virtual bool shouldAnimateRect() const override { return isAlive(); }
    // ~End RectHaverInterface

    // ~Begin ColourHaverInterface
    virtual const Colour& getColour() const override { return colour; }
    virtual void setColour(const Colour& newColour) override { colour = newColour; }
    virtual bool shouldAnimateColour() const override { return isAlive(); }
    // ~End ColourHaverInterface

    void attach(std::unique_ptr<AttachmentBase>&& attachment, const Vector& offset);

    bool isAlive() const { return bAlive; }
    void kill() { bAlive = false; }

protected:
    SDL_Rect rect;
    Colour colour;

    SDL_Rect getBodyRect() const { return DrawingUtils::convertCentredRectToDrawRect(rect); }
    static SDL_Rect getScleraRect(const SDL_Rect& bodyRect);
    static SDL_Rect getPupilRect(const SDL_Rect& scleraRect);

    void drawBody(SDL_Renderer& renderer) const;
    void drawEye(SDL_Renderer& renderer) const;

private:
    bool bAlive = true;
    Vector pupilDisplacement;

    std::vector<std::unique_ptr<AttachmentBase>> attachments;
};