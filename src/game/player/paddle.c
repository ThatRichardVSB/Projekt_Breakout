#include <stdlib.h>

#include "../../helper/SDL.h"
#include "../../helper/global.h"
#include "../game.h"
#include "paddle.h"
#include "../environment/map.h"

// Constructor / Deconstructor
Paddle* createPaddle(const int x, const int y, const int map_y) {
    Paddle* paddle = (Paddle*) malloc(sizeof(Paddle));

    if (paddle == NULL) {
        printf("No more memory!\n");
        exit(1);
    }

    paddle->position.x = x;
    paddle->position.y = map_y;

    paddle->collision = createCollision(0, 0, PADDLE_WIDTH, PADDLE_HEIGHT);

    return paddle;
}

void destroyPaddle(Paddle** const paddle) {
    free(*paddle);
    *paddle = NULL;
}


// Update / Render
void updatePaddle(Paddle* const paddle) {
    paddle->position.x = getMousePos().x - (PADDLE_WIDTH / 2);
}

void renderPaddle(SDL_Renderer* const renderer, const Paddle* const paddle) {
    SDL_Rect rect = {
        .x = paddle->position.x,
        .y = paddle->position.y,
        .w = PADDLE_WIDTH,
        .h = PADDLE_HEIGHT
    };

    SDL_SetRenderDrawColor(renderer, PADDLE_COLOR_R, PADDLE_COLOR_G, PADDLE_COLOR_B, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}