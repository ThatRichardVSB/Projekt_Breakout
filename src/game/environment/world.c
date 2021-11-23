#include <SDL.h>
#include <stdlib.h>

#include "world.h"
#include "map.h"
#include "../player/ball.h"
#include "../player/paddle.h"


// Constructor / Deconstructor
World* createWorld(FILE* mapFile) {
    World* world = (World*) malloc(sizeof(World));

    if (world == NULL) {
        exit(-1);
    }

    world->ball = createBall(0, 0, BALL_SPEED, BALL_SIZE);
    world->paddle = createPaddle(0, 0);
    world->map = createMap(mapFile);

    return world;
}

void destroyWorld(World** _world) {
    World* world = *_world;

    destroyBall(&world->ball);
    destroyPaddle(&world->paddle);
    destroyMap(&world->map);

    free(world);
    *_world = NULL;
}


// Update / Render
void updateWorld(World* world) {
    updateBall(world->ball);
    updatePaddle(world->paddle);
    updateMap(world->map);
}

void renderWorld(SDL_Renderer* renderer, World* world) {
    renderBall(renderer, world->ball);
    renderPaddle(renderer, world->paddle);
    renderMap(renderer, world->map);
}