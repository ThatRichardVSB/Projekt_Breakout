#include <SDL.h>
#include <stdlib.h>

#include "world.h"
#include "map.h"
#include "../../helper/global.h"
#include "../player/ball.h"
#include "../player/paddle.h"


// Constructor / Deconstructor
World* createWorld(SDL_Window* const window, const FILE* mapFile) {
    World* world = (World*) malloc(sizeof(World));

    if (world == NULL) {
        printf("No more memory!\n");
        exit(1);
    }

    unsigned win_h = 0;
    SDL_GetWindowSize(window, NULL, &win_h);

    world->ball = createBall(200, 200, BALL_SPEED, BLOCK_HEIGHT / 2);
    world->paddle = createPaddle(0, 0, win_h - (PADDLE_BOTTOM_BLOCK_MARGIN * BLOCK_HEIGHT));
    world->map = createMap(window, mapFile);

    return world;
}

void destroyWorld(World** const _world) {
    World* world = *_world;

    destroyBall(&world->ball);
    destroyPaddle(&world->paddle);
    destroyMap(&world->map);

    free(world);
    *_world = NULL;
}


// Update / Render
void updateWorld(World* const world, const double deltaTime) {
    updateMap(world->map);
    updatePaddle(world->paddle);
    updateBall(world->ball, world->map, world->paddle, deltaTime);
}

void renderWorld(SDL_Renderer* const renderer, const World* const world) {
    renderBall(renderer, world->ball);
    renderPaddle(renderer, world->paddle);
    renderMap(renderer, world->map);
}