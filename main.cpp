//#include "app.hpp"

#include "SDL.h"

#include <iostream>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "SDL2Test",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
    /*std::cout << "Starting program\n";
    Application app;

    if (!app.setup())
    {
        std::cout << "Setup failed\n";
        return 1;
    }

    std::cout << "Start loop\n";
    app.loop();
    std::cout << "End loop\n";

    return 0;*/
}
