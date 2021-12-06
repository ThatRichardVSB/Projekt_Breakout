#pragma once

#include <SDL.h>

#include "../../helper/global.h"
#include "../environment/map.h"
#include "paddle.h"

#define BALL_SPEED 25
#define BALL_RADIUS (BLOCK_HEIGHT / 2)

#define BALL_SPAWN_HEIGHT BLOCK_HEIGHT

typedef struct {
    Point position;

    float velX;
    float velY;

    int speed;

    CollisionBox collision;
} Ball;

Ball* createBall(const int x, const int y, const int speed, const unsigned int radius);
void destroyBall(Ball** const ball);

void bounceBallHorizontally(Ball* const ball);
void bounceBallVertically(Ball* const ball);

void updateBall(Ball* const ball, const Map* const map, const Paddle* const paddle, Block* const destroyedBlock, const double deltaTime);
void renderBall(SDL_Renderer* const renderer, const Ball* const ball);