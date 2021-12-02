#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

typedef struct {
    unsigned int fontCount;
    TTF_Font** fonts;
} ResourceManager;


ResourceManager* createResourceManager();
void destroyResourceManager(ResourceManager** const manager);

void addResourceFont(ResourceManager* const manager, const char* const filename, const unsigned int size);
TTF_Font* getResourceFont(const ResourceManager* const manager, const char* const name);