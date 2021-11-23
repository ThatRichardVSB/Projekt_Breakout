#include <stdlib.h>

#include "ball.h"
#include "../../helper/global.h"
#include "../../helper/SDL.h"
#include "../environment/map.h"
#include "paddle.h"


// Constructor / Deconstructor
Ball* createBall(const int x, const int y, const int speed, const CollisionBox collision) {
    Ball* ball = (Ball*) malloc(sizeof(Ball));

    if (ball == NULL) {
        printf("No more memory!\n");
        exit(1);
    }

    ball->position.x = x;
    ball->position.y = y;

    ball->velX = -1;//(rand() % 2) ? 1 : -1;
    ball->velY = -1;//(rand() % 2) ? 1 : -1;

    ball->speed = speed;
    ball->collision = collision;

    return ball;
}

void destroyBall(Ball** const ball) {
    free(*ball);
    *ball = NULL;
}


// Functions
void bounceBallHorizontally(Ball* const ball) {
    ball->velX *= -1;
}

void bounceBallVertically(Ball* const ball) {
    ball->velY *= -1;
}


// Update / Render
void updateBall(Ball* const ball, const Map* const map, const Paddle* const paddle, const double deltaTime) {
    const double speed = ball->speed * deltaTime;

    double destX = ball->position.x + (ball->velX * speed);
    double destY = ball->position.y + (ball->velY * speed);

    int dirX = 0;
    int dirY = 0;

    isColliding(ball->position, ball->collision, paddle->position, paddle->collision, &dirX, &dirY);

    for (unsigned int y = 0; y < map->height; y++) {
        for (unsigned int x = 0; x < map->width; x++) {
            Block block = map->blocks[y][x];

            if (block == Air) continue;

            Point blockPos = {
                .x = x * BLOCK_SIZE,
                .y = y * BLOCK_SIZE
            };

            if (isColliding(ball->position, ball->collision, blockPos, BlockCollision, &dirX, &dirY)) {
                printf("Block collision!\n");

                ball->speed = 0;

                bounceBallHorizontally(ball);
                bounceBallVertically(ball);

                goto GO_SkipUpdateBallCheck; // !!! NOT A BAD USE OF GOTO >:( (to get out of nested loop) !!!
            }
        }
    }

    GO_SkipUpdateBallCheck:

    if (dirX) bounceBallHorizontally(ball);
    if (dirY) bounceBallVertically(ball);

    destX = ball->position.x + (ball->velX * speed);
    destY = ball->position.y + (ball->velY * speed);

    ball->position.x = destX;
    ball->position.y = destY;
}

void renderBall(SDL_Renderer* const renderer, const Ball* const ball) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillCircle(renderer, ball->position.x, ball->position.y, (ball->collision.w > ball->collision.h) ? ball->collision.w : ball->collision.h);
}