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

    // Get window size and calculate map size based on it 
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

    // Create space for blocks
    map->blocks = (Block**) malloc(sizeof(Block*) * map->height);
    for (unsigned int i = 0; i < map->height; i++) {
        map->blocks[i] = (Block*) malloc(sizeof(Block) * map->width);
    }

    // Create space for walls and create those walls
    map->walls = (CollisionBox*) malloc(sizeof(CollisionBox) * WALL_COUNT);

    CollisionBox topWall = {
        .x = 0,
        .y = 0,
        .w = WALL_WIDTH * 2 + map->width * BLOCK_WIDTH,
        .h = WALL_WIDTH * 4
    };

    const int horWallY = topWall.y + topWall.h;
    const int horWallHeight = map->height * BLOCK_HEIGHT - topWall.y;

    CollisionBox leftWall = {
        .x = 0,
        .y = horWallY,
        .w = WALL_WIDTH,
        .h = horWallHeight
    };
    CollisionBox rightWall = {
        .x = (leftWall.x + leftWall.w) + map->width * BLOCK_WIDTH,
        .y = horWallY,
        .w = WALL_WIDTH,
        .h = horWallHeight
    };

    map->walls[0] = leftWall;
    map->walls[1] = topWall;
    map->walls[2] = rightWall;

    // Generate the map
    generateMap(map, mapFile);

    return map;
}

void destroyMap(Map** const _map) {
    if (_map == NULL) return;

    Map* map = (Map* const) *_map;

    for (int i = 0; i < map->height; i++) {
        free(map->blocks[i]);
        map->blocks[i] = NULL;
    }
    free(map->blocks);
    map->blocks = NULL;

    free(map);
    *_map = NULL;
}


// Functions
void generateMap(Map* const map, const FILE* const mapFile) {
    // First fill it with air
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            map->blocks[y][x] = Air;
        }
    }

    if (mapFile == NULL) { // Default Layout
        Block block = Red;
        for (int y = MAP_START_Y; y < MAP_START_Y + 4 * 2; y++) {
            for (int x = 0; x < map->width; x++) {
                map->blocks[y][x] = block;
            }

            if ((y - MAP_START_Y) != 0 && ((y - MAP_START_Y) + 1) % 2 == 0) block -= (Red - Orange);
        }
    } else { // Load from file

    }
}

int getBlockCountMap(const Map* const map) {
    int count = 0;

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
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