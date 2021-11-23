#pragma once

#include <SDL.h>

#define BALL_SPEED 10
#define BALL_SIZE 32

typedef struct {
    int x;
    int y;

    int velX;
    int velY;

    int size;
    int speed;
} Ball;

Ball* createBall(int x, int y, int speed, int size);
void destroyBall(Ball** ball);

void updateBall(Ball* ball);

void bounceBallHorizontally(Ball* ball);
void bounceBallVertically(Ball* ball);

void renderBall(SDL_Renderer* renderer, Ball* ball);