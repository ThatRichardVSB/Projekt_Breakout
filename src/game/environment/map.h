#pragma once

#include <SDL.h>

#include "../../helper/global.h"

#define BLOCK_HEIGHT 26
#define BLOCK_WIDTH (BLOCK_HEIGHT * 3)
#define BLOCK_PADDING 2

#define WALL_WIDTH BLOCK_HEIGHT
#define WALL_COUNT 3

#define MAP_START_Y 5

typedef enum {
    Air = 0,
    Yellow = 1,
    Green = 3,
    Orange = 5,
    Red = 7
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

void generateMap(Map* const map, const FILE* const mapFile);
int getBlockCountMap(const Map* const map);

void updateMap(Map* const map);
void renderMap(SDL_Renderer* const renderer, const Map* const map);