#include <stdlib.h>

#include "../../helper/SDL.h"
#include "../game.h"
#include "paddle.h"


// Constructor / Deconstructor
Paddle* createPaddle(int x, int y) {
    Paddle* paddle = (Paddle*) malloc(sizeof(Paddle));

    if (paddle == NULL) {
        exit(-1);
    }

    paddle->position.x = x;
    paddle->position.y = y;

    return paddle;
}

void destroyPaddle(Paddle** paddle) {
    free(*paddle);
    *paddle = NULL;
}


// Update / Render
void updatePaddle(Paddle* paddle) {
    paddle->position = getMousePos();
}

void renderPaddle(SDL_Renderer* renderer, Paddle* paddle) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawFillCircle(renderer, paddle->position.x, paddle->position.y, 20);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawCircle(renderer, paddle->position.x, paddle->position.y, 20);
}