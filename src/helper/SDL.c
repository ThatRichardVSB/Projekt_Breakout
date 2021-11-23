#include <SDL.h>

#include "SDL.h"

// -- CREDIT: https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c
void SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    int offsetX = 0, offsetY = radius, d = radius - 1;
    int status = 0;

    while (offsetY >= offsetX) {
        status += SDL_RenderDrawPoint(renderer, x + offsetX, y + offsetY);
        status += SDL_RenderDrawPoint(renderer, x + offsetY, y + offsetX);
        status += SDL_RenderDrawPoint(renderer, x - offsetX, y + offsetY);
        status += SDL_RenderDrawPoint(renderer, x - offsetY, y + offsetX);
        status += SDL_RenderDrawPoint(renderer, x + offsetX, y - offsetY);
        status += SDL_RenderDrawPoint(renderer, x + offsetY, y - offsetX);
        status += SDL_RenderDrawPoint(renderer, x - offsetX, y - offsetY);
        status += SDL_RenderDrawPoint(renderer, x - offsetY, y - offsetX);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetX) {
            d -= 2 * offsetX + 1;
            offsetX += 1;
        } else if (d < 2 * (radius - offsetY)) {
            d += 2 * offsetY - 1;
            offsetY -= 1;
        } else {
            d += 2 * (offsetY - offsetX - 1);
            offsetY -= 1;
            offsetX += 1;
        }
    }
}

void SDL_RenderDrawFillCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int diff_x = radius - w;
            int diff_y = radius - h;

            if ((diff_x * diff_x + diff_y * diff_y) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + diff_x, y + diff_y);
            }
        }
    }
}