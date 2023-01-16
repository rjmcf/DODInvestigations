#pragma once

#include "animations/animationController.hpp"
#include "colour.hpp"
#include "drawCall.hpp"
#include "enemies/enemyController.hpp"
#include "events/bgColourChangeEventListener.hpp"

#include "Tracy.hpp"

#include <SDL.h>

#include <condition_variable>
#include <mutex>
#include <thread>

class Enemy;

class Application
{
public:
   ~Application();

    bool setup();
    void start();

private:
    std::thread logic_thread;
    std::condition_variable_any condDrawCallsFull;
    std::condition_variable_any condDrawCallsEmpty;
    std::vector<std::unique_ptr<const DrawCall>> drawCalls;
    TracyLockable(std::mutex, drawCallsMutex);

    // Logic side
    void loop();
    void update(int deltaTimeMs);
    void populateDrawCalls();
    EnemyController enemyController;
    AnimationController animationController;
    Colour bgColour{0,10,20,255};
    BgColourEventListener bgColourEventListener;
    SDL_Event windowEvent;
    bool bShouldQuit = false;
    bool bNeedPause = false;
    bool bNeedUnpause = false;
    bool bNeedKill = false;

    // Drawing side
    void executeDrawCalls();
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
