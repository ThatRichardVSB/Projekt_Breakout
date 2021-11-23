#pragma once

#include <SDL.h>
#include "map.h"
#include "../player/ball.h"
#include "../player/paddle.h"

typedef struct {
    Paddle* paddle;
    Ball* ball;

    Map* map;
} World;

World* createWorld();
void destroyWorld(World** world);

void updateWorld(World* world);
void renderWorld(SDL_Renderer* renderer, World* world);