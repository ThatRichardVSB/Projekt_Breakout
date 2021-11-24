#include <stdlib.h>
#include <SDL.h>

#include "world.h"
#include "map.h"
#include "../player/paddle.h"

const CollisionBox BlockCollision = {
    .x = 0,
    .y = 0,
    .w = BLOCK_WIDTH,
    .h = BLOCK_HEIGHT
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

    const unsigned int map_width = win_w - WALL_WIDTH * 2;
    const unsigned int map_height = win_h - WALL_WIDTH * 2;

    map->width = map_width / BLOCK_WIDTH;
    map->height = map_height / BLOCK_HEIGHT;

    if (map_width % BLOCK_WIDTH != 0 || map_height % BLOCK_HEIGHT != 0) {
        printf("Invalid window size for map!\n");
        exit(1);
    }

    map->blocks = (Block**) malloc(sizeof(Block*) * map->height);
    for (unsigned int i = 0; i < map->height; i++) {
        map->blocks[i] = (Block*) malloc(sizeof(Block) * map->width);
    }

    map->walls = (CollisionBox*) malloc(sizeof(CollisionBox) * WALL_COUNT);

    CollisionBox leftWall = {
        .x = 0,
        .y = WALL_WIDTH,
        .w = WALL_WIDTH,
        .h = map->height * BLOCK_HEIGHT
    };
    CollisionBox topWall = {
        .x = 0,
        .y = 0,
        .w = WALL_WIDTH * 2 + map->width * BLOCK_WIDTH,
        .h = WALL_WIDTH
    };
    CollisionBox rightWall = {
        .x = WALL_WIDTH + map->width * BLOCK_WIDTH,
        .y = 0,
        .w = WALL_WIDTH,
        .h = map->height * BLOCK_HEIGHT
    };

    map->walls[0] = leftWall;
    map->walls[1] = topWall;
    map->walls[2] = rightWall;

    // Place Air
    for (unsigned int y = 0; y < map->height; y++) {
        for (unsigned int x = 0; x < map->width; x++) {
            Block block = Air;

            map->blocks[y][x] = Air;
        }
    }

    if (mapFile == NULL) { // Default Layout
        for (unsigned int y = 1; y < 9; y++) {
            for (unsigned int x = 1; x < map->width - 1; x++) {
                Block block = rand() % (Red - Yellow + 1) + Yellow;

                map->blocks[y][x] = block;
            }
        }
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
                .x = WALL_WIDTH + x * BLOCK_WIDTH,
                .y = WALL_WIDTH + y * BLOCK_HEIGHT,
                .w = BLOCK_WIDTH,
                .h = BLOCK_HEIGHT
            };

            int r = 255, g = 255, b = 255;
            switch (block) {
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

    for (unsigned int i = 0; i < WALL_COUNT; i++) {
        CollisionBox* wall = &map->walls[i];

        SDL_SetRenderDrawColor(renderer, 125, 125, 125, SDL_ALPHA_OPAQUE);

        SDL_Rect rect = {
            .x = wall->x,
            .y = wall->y,
            .w = wall->w,
            .h = wall->h
        };

        SDL_RenderFillRect(renderer, &rect);
    }
}