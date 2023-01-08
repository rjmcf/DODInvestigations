#include "app.hpp"

#include "oopVersion/animations/animationTranslate.hpp"
#include "oopVersion/easing/easingFunction.hpp"
#include "oopVersion/enemies/enemyWithHealth.hpp"

#include <iostream>

const int WIDTH = 800, HEIGHT = 600;

Application::~Application()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
}

bool Application::setup()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialise SDL2: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (!window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    enemy1 = std::make_unique<EnemyWithHealth>(120,150, 20,20, Colour{255,0,0,255}, 100);
    enemy2 = std::make_unique<EnemyWithHealth>(140,150, 20,20, Colour{255,0,0,255}, 100);

    return true;
}

void Application::loop()
{
    int frameStart = 0, frameEnd = 0, deltaTime = 0;
    while (!bShouldQuit)
    {
        frameStart = SDL_GetTicks();
        update(deltaTime);
        draw();
        frameEnd = SDL_GetTicks();
        deltaTime = frameEnd - frameStart;

        // Ensure at least one ms has passed, so we don't end up with deltaTimes of 0
        if (deltaTime < 1)
        {
            SDL_Delay(1);
            frameEnd = SDL_GetTicks();
            deltaTime = frameEnd - frameStart;
        }
    }
}

void Application::update(int deltaTimeMs)
{
    if (SDL_PollEvent(&windowEvent))
    {
        switch (windowEvent.type)
        {
            case SDL_QUIT:
                bShouldQuit = true;
                break;
            case SDL_KEYUP:
            {
                switch (windowEvent.key.keysym.sym)
                {
                    case SDLK_s:
                    {
                        if (enemy1 && enemy2)
                        {
                            animation1 = std::make_unique<AnimationTranslate>(3000, Point{120,150}, Point{120,400}, *enemy1.get(), std::make_unique<NoEase>());
                            animation2 = std::make_unique<AnimationTranslate>(3000, Point{140,150}, Point{140,400}, *enemy2.get(), std::make_unique<EaseIn2Out2>());
                        }
                        break;
                    }
                    case SDLK_p:
                    {
                        if (animation1 && animation2)
                        {
                            animation1->pause();
                            animation2->pause();
                        }
                        break;
                    }
                    case SDLK_u:
                    {
                        if (animation1 && animation2)
                        {
                            animation1->unpause();
                            animation2->unpause();
                        }
                        break;
                    }
                }
                break;
            }
        }
    }

    if (animation1 && animation2)
    {
        animation1->update(deltaTimeMs);
        if (animation1->isComplete())
        {
            animation1->reset();
        }

        animation2->update(deltaTimeMs);
        if (animation2->isComplete())
        {
            animation2->reset();
        }
    }
}

void Application::draw()
{
    if (renderer)
    {
        SDL_RenderClear(renderer);
        if (enemy1 && enemy2)
        {
            enemy1->draw(*renderer);
            enemy2->draw(*renderer);
        }
        SDL_RenderPresent(renderer);
    }
}
