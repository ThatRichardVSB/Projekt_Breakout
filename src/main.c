#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL.h>

#include "game/game.h"
#include "game/environment/map.h"

#define WINDOW_WIDTH (BLOCK_SIZE * 48)
#define WINDOW_HEIGHT (BLOCK_SIZE * 32)

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

    SDL_Event event;
    bool quit = false;
    while (!quit) {
        eventClearGame(game);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    quit = true;
                } break;
            }

            eventGame(game, event);
        }

        updateGame(game);

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