#include "app.hpp"

#include "animations/animationLibrary/animationLibrary.hpp"
#include "scene/scene.hpp"
#include "utils/globals.hpp"

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

    Globals::animationController = &animationController;
    Globals::enemyController = &enemyController;
    Globals::eventManager = &eventManager;

    AnimationLibrary::initialise();

    Scene scene;
    scene.setUp();

    bgColourEventListener.setUp(&bgColour);

    return true;
}

void Application::start()
{
    logic_thread = std::thread(&Application::loop, this);

    while (!bShouldQuit)
    {
#if PROFILING
        TracyCZoneN(inputCtx, "Handle Input", true);
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
                            bNeedPause = true;
                            break;
                        case SDLK_u:
                            bNeedUnpause = true;
                            break;
                        case SDLK_k:
                            bNeedKill = true;
                            break;
                    }
                    break;
                }
            }
        }
#if PROFILING
        TracyCZoneEnd(inputCtx);
#endif // PROFILING

#if PROFILING
        TracyCZoneN(waitFullCtx, "WaitForFull", true);
        std::unique_lock<LockableBase(std::mutex)> lock(drawCallsMutex);
#else
        std::unique_lock lock(drawCallsMutex);
#endif // PROFILING
        condDrawCallsFull.wait(lock, [this](){ return !drawCalls.empty(); });
#if PROFILING
        TracyCZoneEnd(waitFullCtx);
#endif // PROFILING

        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
#if PROFILING
        TracyCZoneN(executeDrawCtx, "ExecuteDraw", true);
#endif // PROFILING
        executeDrawCalls();
#if PROFILING
        TracyCZoneEnd(executeDrawCtx);
#endif // PROFILING

        lock.unlock();
        condDrawCallsEmpty.notify_one();

#if PROFILING
        ZoneNamedN(ZoneDrawRenderPresent, "DrawRenderPresent", true);
#endif // PROFILING

        SDL_RenderPresent(renderer);

#if PROFILING
        FrameMark;
#endif // PROFILING
    }

    logic_thread.join();
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

#if PROFILING
        TracyCZoneN(ctx, "WaitForEmpty", true);
        std::unique_lock<LockableBase(std::mutex)> lock(drawCallsMutex);
#else
        std::unique_lock lock(drawCallsMutex);
#endif // PROFILING
        condDrawCallsEmpty.wait(lock, [this](){ return drawCalls.empty(); });
#if PROFILING
        TracyCZoneEnd(ctx);
#endif // PROFILING

        update(deltaTime);
        populateDrawCalls();
        frameEnd = SDL_GetTicks();
        deltaTime = frameEnd - frameStart;

        lock.unlock();
        condDrawCallsFull.notify_one();
    }
}

void Application::update(int deltaTimeMs)
{
#if PROFILING
    ZoneScoped;
#endif // PROFILING

    if (bNeedPause)
    {
        animationController.pauseAllAnimations();
        bNeedPause = false;
    }
    if (bNeedUnpause)
    {
        animationController.unpauseAllAnimations();
        bNeedUnpause = false;
    }
    if (bNeedKill)
    {
        enemyController.killHalfEnemies();
        bNeedKill = false;
    }

    animationController.updateAllAnimations(deltaTimeMs);
    enemyController.update(deltaTimeMs);
}

void Application::populateDrawCalls()
{
    if (renderer)
    {
        drawCalls.emplace_back(std::make_unique<DrawCallBackground>(bgColour));

        enemyController.drawAllEnemies(drawCalls);
    }
}

void Application::executeDrawCalls()
{
    for (const std::unique_ptr<const DrawCall>& drawCall : drawCalls)
    {
        drawCall->draw(*renderer);
    }

    drawCalls.clear();
}
