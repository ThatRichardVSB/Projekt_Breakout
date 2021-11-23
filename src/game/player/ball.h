#pragma once

#include <SDL.h>

#include "../../helper/global.h"
#include "../environment/map.h"
#include "paddle.h"

#define BALL_SPEED 10

typedef struct {
    Point position;

    int velX;
    int velY;

    int speed;

    CollisionBox collision;
} Ball;

Ball* createBall(const int x, const int y, const int speed, const CollisionBox collision);
void destroyBall(Ball** const ball);

void updateBall(Ball* const ball, const Map* const map, const Paddle* const paddle, const double deltaTime);

void bounceBallHorizontally(Ball* const ball);
void bounceBallVertically(Ball* const ball);

void renderBall(SDL_Renderer* const renderer, const Ball* const ball);