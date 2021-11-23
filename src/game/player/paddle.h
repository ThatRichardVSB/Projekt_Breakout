#pragma once

#include <SDL.h>
#include "../../helper/global.h"

typedef struct {
    Point position;
} Paddle;

Paddle* createPaddle(int x, int y);
void destroyPaddle(Paddle** paddle);

void updatePaddle(Paddle* paddle);
void renderPaddle(SDL_Renderer* renderer, Paddle* paddle);