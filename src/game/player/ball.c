#include <stdlib.h>

#include "ball.h"
#include "../game.h"
#include "../../helper/global.h"
#include "../../helper/SDL.h"
#include "../environment/map.h"
#include "paddle.h"


// Constructor / Deconstructor
Ball* createBall(const int x, const int y, const int speed, const unsigned int radius) {
    Ball* ball = (Ball*) malloc(sizeof(Ball));

    if (ball == NULL) {
        printf("No more memory!\n");
        exit(1);
    }

    ball->position.x = x;
    ball->position.y = y;

    ball->velX = (rand() % 2) ? 1 : -1;
    ball->velY = (rand() % 2) ? 1 : -1;

    ball->speed = speed;

    CollisionBox collision = {
        .x = -radius,
        .y = -radius,
        .w = radius * 2,
        .h = radius * 2
    };
    ball->collision = collision;

    return ball;
}

void destroyBall(Ball** const ball) {
    free(*ball);
    *ball = NULL;
}


// Functions
void changeBallDirection(Ball* const ball, const int dirX, const int dirY) {
    if (dirX != 0) ball->velX = (dirX < 0) ? -1 : 1;
    if (dirY != 0) ball->velY = (dirY < 0) ? -1 : 1;
}


// Update / Render
void updateBall(Ball* const ball, const Map* const map, const Paddle* const paddle, const double deltaTime) {
    const double speed = ball->speed * deltaTime;

    double destX = ball->position.x + (ball->velX * speed);
    double destY = ball->position.y + (ball->velY * speed);

    int dirX = 0;
    int dirY = 0;

    if (!isColliding(ball->position, ball->collision, paddle->position, paddle->collision, &dirX, &dirY)) {
        for (unsigned int y = 0; y < map->height; y++) {
            for (unsigned int x = 0; x < map->width; x++) {
                Block block = map->blocks[y][x];

                if (block == Air) continue;

                Point blockPos = {
                    .x = (map->walls[0].x + map->walls[0].w) + x * BLOCK_WIDTH,
                    .y = (map->walls[1].y + map->walls[1].h) + y * BLOCK_HEIGHT
                };

                if (isColliding(ball->position, ball->collision, blockPos, BlockCollision, &dirX, &dirY)) {
                    if (block >= Yellow && block <= Red) {
                        map->blocks[y][x] = Air;
                    }

                    goto GO_SkipUpdateBallCheck; // !!! NOT A BAD USE OF GOTO >:( (to get out of a nested loop) !!!
                }
            }
        }

        for (unsigned int i = 0; i < WALL_COUNT; i++) {
            CollisionBox* wall = &map->walls[i];

            Point wallPos = {
                .x = wall->x,
                .y = wall->y
            };

            if (isColliding(ball->position, ball->collision, wallPos, *wall, &dirX, &dirY)) {
                printf("Collision!");
                goto GO_SkipUpdateBallCheck;
            }
        }
    }

    GO_SkipUpdateBallCheck:

    if (dirX) {
        changeBallDirection(ball, dirX, 0);
    } else if (dirY) {
        changeBallDirection(ball, 0, dirY);
    }

    destX = ball->position.x + (ball->velX * speed);
    destY = ball->position.y + (ball->velY * speed);

    destX = getMousePos().x;
    destY = getMousePos().y;

    ball->position.x = destX;
    ball->position.y = destY;
}

void renderBall(SDL_Renderer* const renderer, const Ball* const ball) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    const unsigned int diameter = (ball->collision.w > ball->collision.h) ? ball->collision.w : ball->collision.h;
    SDL_RenderFillCircle(renderer, ball->position.x, ball->position.y, diameter / 2);
}