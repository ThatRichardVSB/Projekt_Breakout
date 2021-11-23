#include <stdlib.h>
#include <SDL.h>

#include "world.h"
#include "map.h"
#include "../player/paddle.h"

const CollisionBox BlockCollision = {
    .x = 0,
    .y = 0,
    .w = BLOCK_SIZE,
    .h = BLOCK_SIZE
};

// Constructor / Deconstructor
Map* createMap(SDL_Window* const window, const FILE* mapFile) {
    Map* map = (Map*) malloc(sizeof(Map));

    if (map == NULL) {
        printf("No more memory!\n");
        exit(1);
    }

    unsigned int win_w = 0;
    unsigned int win_h = 0;

    SDL_GetWindowSize(window, &win_w, &win_h);

    map->width = win_w / BLOCK_SIZE;
    map->height = win_h / BLOCK_SIZE;

    if (win_w % BLOCK_SIZE != 0 || win_h % BLOCK_SIZE != 0) {
        printf("Invalid window size for map!\n");
        exit(1);
    }

    map->blocks = (Block**) malloc(sizeof(Block*) * map->height);
    for (unsigned int i = 0; i < map->height; i++) {
        map->blocks[i] = (Block*) malloc(sizeof(Block) * map->width);
    }

    // Insert walls
    for (unsigned int y = 0; y < map->height; y++) {
        for (unsigned int x = 0; x < map->width; x++) {
            Block block = Air;

            if (x == 0 || x == map->width - 1 || y == 0) {
                if (y == map->height - PADDLE_BOTTOM_BLOCK_MARGIN) {
                    block = PaddleWall;
                } else {
                    block = Wall;
                }
            }

            map->blocks[y][x] = block;
        }
    }

    if (mapFile == NULL) { // Default Layout

    } else { // Load from file

    }

    return map;
}

void destroyMap(Map** const _map) {
    Map* map = (Map* const) *_map;

    for (unsigned int i = 0; i < map->height; i++) {
        free(map->blocks[i]);
        map->blocks[i] = NULL;
    }
    free(map->blocks);
    map->blocks = NULL;

    free(map);
    *_map = NULL;
}


// Update / Render
void updateMap(Map* const map) {

}

void renderMap(SDL_Renderer* const renderer, const Map* const map) {
    for (unsigned int y = 0; y < map->height; y++) {
        for (unsigned int x = 0; x < map->width; x++) {
            Block block = map->blocks[y][x];

            if (block == Air) continue;

            SDL_Rect rect = {
                .x = x * BLOCK_SIZE,
                .y = y * BLOCK_SIZE,
                .w = BLOCK_SIZE,
                .h = BLOCK_SIZE
            };

            int r = 255, g = 255, b = 255;
            switch (block) {
                case Wall: {
                    r = g = b = 125;
                } break;

                case PaddleWall: {
                    r = PADDLE_COLOR_R;
                    g = PADDLE_COLOR_G;
                    b = PADDLE_COLOR_B;
                } break;

                case Yellow: {
                    r = 255;
                    g = 255;
                    b = 0;
                } break;

                case Green: {
                    r = 0;
                    g = 255;
                    b = 0;
                } break;

                case Orange: {
                    r = 255;
                    g = 175;
                    b = 0;
                } break;

                case Red: {
                    r = 255;
                    g = 0;
                    b = 0;
                } break;
            }

            SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}