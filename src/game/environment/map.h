#pragma once

#include <SDL.h>

#define BLOCK_SIZE 20

typedef struct {

} Block;

typedef struct {
    Block* blocks;
} Map;

Map* createMap(FILE* mapFile);
void destroyMap(Map** map);

void updateMap(Map* map);
void renderMap(SDL_Renderer* renderer, Map* map);