#pragma once

#include <SDL.h>
#include "../../helper/global.h"

#define PADDLE_HEIGHT BLOCK_HEIGHT
#define PADDLE_WIDTH BLOCK_WIDTH

#define PADDLE_COLOR_R 0
#define PADDLE_COLOR_G 175
#define PADDLE_COLOR_B 255

typedef struct {
    Point position;
    CollisionBox collision;
} Paddle;

Paddle* createPaddle(const int x, const int y, const int map_y);
void destroyPaddle(Paddle** const paddle);

void updatePaddle(Paddle* const paddle);
void renderPaddle(SDL_Renderer* const renderer, const Paddle* const paddle);