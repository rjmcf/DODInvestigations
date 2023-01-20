#pragma once

#include "colour.hpp"
#include "drawCall.hpp"
#include "events/bgColourChangeEventListener.hpp"

#include "programConfig.h"
#if PROFILING
    #include "Tracy.hpp"
#endif // PROFILING

#include <SDL.h>

#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

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

#if PROFILING
    TracyLockable(std::mutex, drawCallsMutex);
#else
    std::mutex drawCallsMutex;
#endif // PROFILING

    // Logic side
    void loop();
    void update(int deltaTimeMs);
    void populateDrawCalls();
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
