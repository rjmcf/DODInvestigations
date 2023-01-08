#pragma once

#include "oopVersion/enemies/enemyController.hpp"

#include <memory>
#include <SDL2/SDL.h>

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

    bool bShouldQuit = false;
};
