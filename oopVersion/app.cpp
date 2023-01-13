#include "app.hpp"

#include "scene/scene.hpp"

#include "programConfig.h"
#if PROFILING
    #include "Tracy.hpp"
    #include "TracyC.h"
#endif // PROFILING

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
#if PROFILING
    ZoneScopedN("Application set up");
    TracyCZoneN(ctx, "SDL Setup", true);
#endif // PROFILING

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

#if PROFILING
    TracyCZoneEnd(ctx);
#endif // PROFILING

    Scene scene;
    scene.setUp(enemyController, animationController);

    bgColourEventListener.setUp(&bgColour);

    return true;
}

void Application::loop()
{
    int frameStart = 0, frameEnd = 0, deltaTime = 0;
    while (!bShouldQuit)
    {
#if PROFILING
        ZoneNamedN(ZoneLoop, "Loop", true);
#endif // PROFILING
        frameStart = SDL_GetTicks();
        update(deltaTime);
        draw();
        frameEnd = SDL_GetTicks();
        deltaTime = frameEnd - frameStart;

#if PROFILING
        ZoneNamedN(ZoneLoopDelay, "LoopDelay", true);
#endif // PROFILING
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
#if PROFILING
    ZoneScoped;
    TracyCZoneN(ctx, "Handle Input", true);
#endif // PROFILING

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
                    case SDLK_k:
                        enemyController.killHalfEnemies();
                        break;
                }
                break;
            }
        }
    }

#if PROFILING
    TracyCZoneEnd(ctx);
#endif // PROFILING

    enemyController.update(deltaTimeMs);
    animationController.updateAllAnimations(deltaTimeMs);
}

void Application::draw()
{
#if PROFILING
    ZoneNamedN(ZoneDraw, "Draw", true);
#endif // PROFILING

    if (renderer)
    {
        SDL_RenderClear(renderer);

        drawBackground();
        enemyController.drawAllEnemies(*renderer);

#if PROFILING
        ZoneNamedN(ZoneDrawRenderPresent, "DrawRenderPresent", true);
#endif // PROFILING

        SDL_RenderPresent(renderer);

#if PROFILING
        FrameMark;
#endif // PROFILING
    }
}

void Application::drawBackground()
{
    SDL_SetRenderDrawColor(renderer, bgColour.red, bgColour.green, bgColour.blue, bgColour.alpha);
    SDL_RenderFillRect(renderer, nullptr);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
