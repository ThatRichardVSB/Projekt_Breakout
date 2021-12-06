#include <stdio.h>
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
Map* createMap(SDL_Window* const window, char* const mapFilename) {
    Map* map = (Map*) malloc(sizeof(Map));

    if (map == NULL) {
        exit(1);
    }

    // Create space for walls and create those walls
    map->walls = (CollisionBox*) malloc(sizeof(CollisionBox) * WALL_COUNT);

    if (map->walls == NULL) {
        exit(1);
    }

    // Get window size and calculate map size based on it 
    int win_w = 0;
    int win_h = 0;

    SDL_GetWindowSize(window, &win_w, &win_h);

    const unsigned int map_width = win_w - WALL_WIDTH * 2;
    map->width = map_width / BLOCK_WIDTH;

    CollisionBox topWall = {
        .x = 0,
        .y = 0,
        .w = WALL_WIDTH * 2 + map->width * BLOCK_WIDTH,
        .h = WALL_WIDTH * 4
    };

    const unsigned int map_height = win_h - (topWall.y + topWall.h) - WALL_WIDTH * 4;
    map->height = map_height / BLOCK_HEIGHT;

    if (map_width % BLOCK_WIDTH != 0 || map_height % BLOCK_HEIGHT != 0) {
        printf("Invalid window size for map!\n");
        exit(1);
    }

    // Create space for blocks
    map->blocks = (Block**) malloc(sizeof(Block*) * map->height);

    if (map->blocks == NULL) {
        exit(1);
    }

    for (unsigned int i = 0; i < map->height; i++) {
        map->blocks[i] = (Block*) malloc(sizeof(Block) * map->width);

        if (map->blocks[i] == NULL) {
            exit(1);
        }
    }

    // Put horizontal walls after making space for blocks
    const int horWallY = topWall.y + topWall.h;
    const int horWallHeight = map->height * BLOCK_HEIGHT + WALL_WIDTH * 3;

    CollisionBox leftWall = {
        .x = 0,
        .y = horWallY,
        .w = WALL_WIDTH,
        .h = horWallHeight
    };
    CollisionBox rightWall = {
        .x = (leftWall.x + leftWall.w) + (map->width * BLOCK_WIDTH),
        .y = horWallY,
        .w = WALL_WIDTH,
        .h = horWallHeight
    };

    map->walls[0] = leftWall;
    map->walls[1] = topWall;
    map->walls[2] = rightWall;

    map->filename = mapFilename;

    // Generate the map
    generateMap(map);

    return map;
}

void destroyMap(Map** const _map) {
    if (_map == NULL) return;

    Map* const map = *_map;

    if (map == NULL) return;

    if (map->blocks != NULL) {
        free(map->blocks);

        map->blocks = NULL;
    }

    free(map);
    *_map = NULL;
}


// Functions
void generateMap(Map* const map) {
    // First fill it with air
    for (unsigned int y = 0; y < map->height; y++) {
        for (unsigned int x = 0; x < map->width; x++) {
            map->blocks[y][x] = Air;
        }
    }

    FILE* mapFile = NULL;

    if (map->filename != NULL) {
        mapFile = fopen(map->filename, "rt");
    }

    if (mapFile == NULL) { // Default Layout
        Block block = Red;
        for (unsigned int y = MAP_START_Y; y < MAP_START_Y + 4 * 2; y++) {
            for (unsigned int x = 0; x < map->width; x++) {
                map->blocks[y][x] = block;
            }

            const int offsetY = y - MAP_START_Y;
            if (offsetY != 0 && (offsetY + 1) % 2 == 0) block -= (Red - Orange);
        }
    } else { // Load from file
        for (unsigned int y = 0; y < map->height; y++) {
            for (unsigned int x = 0; x < map->width; x++) {
                if (feof(mapFile)) {
                    goto GOTO_MapEndOfFile;
                }

                int value;
                fscanf(mapFile, "%d ", &value);

                Block block;
                switch (value) {
                    case 0: {
                        block = Air;
                    } break;

                    case 1: {
                        block = Yellow;
                    } break;

                    case 2: {
                        block = Green;
                    } break;

                    case 3: {
                        block = Orange;
                    } break;

                    case 4: {
                        block = Red;
                    } break;
                }

                map->blocks[y][x] = block;
            }
        }

        GOTO_MapEndOfFile:

        fclose(mapFile);
    }
}

int getBlockCountMap(const Map* const map) {
    int count = 0;

    for (unsigned int y = 0; y < map->height; y++) {
        for (unsigned int x = 0; x < map->width; x++) {
            if (map->blocks[y][x] != Air) count++;
        }
    }

    return count;
}


// Update / Render
void updateMap(Map* const map) {
    if (map == NULL) return;
}

void renderMap(SDL_Renderer* const renderer, const Map* const map) {
    if (map == NULL) return;

    for (unsigned int y = 0; y < map->height; y++) {
        for (unsigned int x = 0; x < map->width; x++) {
            Block block = map->blocks[y][x];

            if (block == Air) continue;

            SDL_Rect rect = {
                .x = (map->walls[0].x + map->walls[0].w) + x * BLOCK_WIDTH + BLOCK_PADDING,
                .y = (map->walls[1].y + map->walls[1].h) + y * BLOCK_HEIGHT + BLOCK_PADDING,
                .w = BLOCK_WIDTH - BLOCK_PADDING,
                .h = BLOCK_HEIGHT - BLOCK_PADDING
            };

            int r = 255, g = 255, b = 255, a = SDL_ALPHA_OPAQUE;
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

                default: {
                    a = 0;
                } break;
            }

            SDL_SetRenderDrawColor(renderer, r, g, b, a);
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