#pragma once

#include "oopVersion/animations/animationController.hpp"
#include "oopVersion/enemies/enemyController.hpp"
#include "oopVersion/events/dummyEventListener.hpp"

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
    void drawRectangle();

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event windowEvent;

    EnemyController enemyController;
    AnimationController animationController;

    DummyEventListener dummyEventListener;

    bool bShouldQuit = false;
};
