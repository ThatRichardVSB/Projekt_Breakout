#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL.h>

#include "game/game.h"
#include "game/environment/map.h"

#define WINDOW_WIDTH (WALL_WIDTH * 2 + BLOCK_WIDTH * 14)
#define WINDOW_HEIGHT (WALL_WIDTH * 2 + BLOCK_HEIGHT * 26)

int main() {
    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Breakout",
        100, 100,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    Game* game = createGame(renderer, window, WorldScene);

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;

    double deltaTime = 0;
    while (!game->quit) {
        SDL_Event event;

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double) ((NOW - LAST) * 1000 / (double) SDL_GetPerformanceFrequency()) / 100;

        eventClearGame(game);

        while (SDL_PollEvent(&event)) {
            eventGame(game, event);
        }

        updateGame(game, deltaTime);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        renderGame(game);

        SDL_RenderPresent(renderer);
    }

    destroyGame(&game);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}