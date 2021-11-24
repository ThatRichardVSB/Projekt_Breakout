#pragma once

#include <SDL.h>

#include "../../helper/global.h"

#define BLOCK_HEIGHT 26
#define BLOCK_WIDTH (BLOCK_HEIGHT * 3)

#define WALL_WIDTH BLOCK_HEIGHT
#define WALL_COUNT 3

typedef enum {
    Air,
    Yellow,
    Green,
    Orange,
    Red
} Block;

typedef struct {
    CollisionBox* walls;
    Block** blocks;

    unsigned int width;
    unsigned int height;
} Map;

extern const CollisionBox BlockCollision;

Map* createMap(SDL_Window* const window, const FILE* mapFile);
void destroyMap(Map** const map);

void updateMap(Map* const map);
void renderMap(SDL_Renderer* const renderer, const Map* const map);