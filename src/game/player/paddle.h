#pragma once

#include <SDL.h>
#include "../../helper/global.h"

#define PADDLE_HEIGHT BLOCK_HEIGHT
#define PADDLE_WIDTH BLOCK_WIDTH * 2

#define PADDLE_COLOR_R 0
#define PADDLE_COLOR_G 175
#define PADDLE_COLOR_B 255

#define PADDLE_SPEED 35

typedef struct {
    Point position;
    CollisionBox collision;

    CollisionBox* walls;
} Paddle;


Paddle* createPaddle(const int x, const int map_y, CollisionBox* const walls);
void destroyPaddle(Paddle** const paddle);

void updatePaddle(Paddle* const paddle, const double deltaTime);
void renderPaddle(SDL_Renderer* const renderer, const Paddle* const paddle);