#pragma once

#include "animations/animationController.hpp"
#include "colour.hpp"
#include "enemies/enemyController.hpp"
#include "events/bgColourChangeEventListener.hpp"

#include <SDL.h>

class Enemy;

class Application
{
public:
   ~Application();

    bool setup();
    void loop();

private:
    // Delta Time in ms
    void update(int deltaTimeMs);
    void draw();
    void drawBackground();

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event windowEvent;

    EnemyController enemyController;
    AnimationController animationController;

    Colour bgColour{0,10,20,255};
    BgColourEventListener bgColourEventListener;

    bool bShouldQuit = false;
};
