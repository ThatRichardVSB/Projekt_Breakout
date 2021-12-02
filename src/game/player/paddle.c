#include <stdlib.h>

#include "../../helper/SDL.h"
#include "../../helper/global.h"
#include "../game.h"
#include "paddle.h"
#include "../environment/map.h"

double deltaTime;

// Constructor / Deconstructor
Paddle* createPaddle(const int x, const int map_y, CollisionBox* const walls) {
    Paddle* paddle = (Paddle*) malloc(sizeof(Paddle));

    if (paddle == NULL) {
        exit(1);
    }

    paddle->position.x = x;
    paddle->position.y = map_y;

    paddle->collision = createCollision(-PADDLE_WIDTH / 2, 0, PADDLE_WIDTH, PADDLE_HEIGHT);

    paddle->walls = walls;

    return paddle;
}

void destroyPaddle(Paddle** const paddle) {
    if (paddle == NULL) return;

    free(*paddle);
    *paddle = NULL;
}


// Update / Render
void updatePaddle(Paddle* const paddle, const double deltaTime) {
    if (paddle == NULL) return;

    bool left = isKeyPressed(SDLK_a) || isKeyPressed(SDLK_LEFT);
    bool right = isKeyPressed(SDLK_d) || isKeyPressed(SDLK_RIGHT);

    Point new_pos = {
        .x = paddle->position.x + (right - left) * deltaTime * PADDLE_SPEED,
        .y = paddle->position.y
    };

    for (unsigned int i = 0; i < WALL_COUNT; i++) {
        const Point wallPos = {
            .x = 0,
            .y = 0
        };

        if (isColliding(new_pos, paddle->collision, wallPos, paddle->walls[i], NULL, NULL)) {
            new_pos.x = paddle->position.x;
        }
    }

    paddle->position.x = new_pos.x;
}

void renderPaddle(SDL_Renderer* const renderer, const Paddle* const paddle) {
    if (paddle == NULL) return;

    SDL_Rect rect = {
        .x = paddle->position.x - PADDLE_WIDTH / 2,
        .y = paddle->position.y,
        .w = PADDLE_WIDTH,
        .h = PADDLE_HEIGHT
    };

    SDL_SetRenderDrawColor(renderer, PADDLE_COLOR_R, PADDLE_COLOR_G, PADDLE_COLOR_B, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}