#include <stdlib.h>
#include "ball.h"


// Constructor / Deconstructor
Ball* createBall(int x, int y, int speed, int size) {
    Ball* ball = (Ball*) malloc(sizeof(Ball));

    if (ball == NULL) {
        exit(-1);
    }

    ball->x = x;
    ball->y = y;

    ball->velX = (rand() % 2) ? 1 : -1;
    ball->velY = (rand() % 2) ? 1 : -1;

    ball->speed = speed;
    ball->size = size;

    return ball;
}

void destroyBall(Ball** ball) {
    free(*ball);
    *ball = NULL;
}


// Functions
void bounceBallHorizontally(Ball* ball) {
    ball->velX *= -1;
}

void bounceBallVertically(Ball* ball) {
    ball->velY *= -1;
}


// Update / Render
void updateBall(Ball* ball) {
    ball->x += ball->velX * ball->speed;
    ball->y += ball->velY * ball->speed;
}

void renderBall(SDL_Renderer* renderer, Ball* ball) {

}