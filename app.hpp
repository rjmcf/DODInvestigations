#pragma once

#include "oopVersion/animations/animation.hpp"
#include "oopVersion/enemies/enemy.hpp"

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

    std::unique_ptr<Enemy> enemy;
    std::unique_ptr<Animation> animation;

    bool bShouldQuit = false;
};
