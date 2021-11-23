#pragma once

#include <SDL.h>

#include "../../helper/global.h"

#define BLOCK_SIZE 20

typedef enum {
    Air,
    Wall,
    PaddleWall,
    Yellow,
    Green,
    Orange,
    Red
} Block;

typedef struct {
    Block** blocks;

    unsigned int width;
    unsigned int height;
} Map;

extern const CollisionBox BlockCollision;

Map* createMap(SDL_Window* const window, const FILE* mapFile);
void destroyMap(Map** const map);

void updateMap(Map* const map);
void renderMap(SDL_Renderer* const renderer, const Map* const map);