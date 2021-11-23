#pragma once

#include <SDL.h>
#include "map.h"
#include "../player/ball.h"
#include "../player/paddle.h"

#define PADDLE_BOTTOM_BLOCK_MARGIN 2

typedef struct {
    Paddle* paddle;
    Ball* ball;

    Map* map;
} World;

World* createWorld(SDL_Window* const window, const FILE* mapFile);
void destroyWorld(World** const world);

void updateWorld(World* const world, const double deltaTime);
void renderWorld(SDL_Renderer* const renderer, const World* const world);