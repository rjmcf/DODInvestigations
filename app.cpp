#include "app.hpp"

#include "oopVersion/scene/scene.hpp"

#include <iostream>

const int WIDTH = 1600, HEIGHT = 900;

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

    Scene scene;
    scene.setUp(enemyController, animationController);

    dummyEventListener.setUp();

    std::cout << "Setup Complete\n";

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
                    case SDLK_p:
                        animationController.pauseAllAnimations();
                        break;
                    case SDLK_u:
                        animationController.unpauseAllAnimations();
                        break;
                }
                break;
            }
        }
    }

    enemyController.update(deltaTimeMs);
    animationController.updateAllAnimations(deltaTimeMs);
}

void Application::draw()
{
    if (renderer)
    {
        SDL_RenderClear(renderer);
        enemyController.drawAllEnemies(*renderer);
        SDL_RenderPresent(renderer);
    }
}
