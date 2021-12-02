#include <stdlib.h>
#include <string.h>
#include <SDL_ttf.h>

#include "resource_manager.h"

// Constructor / Deconstructor
ResourceManager* createResourceManager() {
    ResourceManager* manager = (ResourceManager*) malloc(sizeof(ResourceManager));

    if (manager == NULL) {
        exit(1);
    }

    TTF_Init();

    manager->fontCount = 0;
    manager->fonts = NULL;

    addResourceFont(manager, "arial.ttf", 26);

    return manager;
}

void destroyResourceManager(ResourceManager** const _manager) {
    if (_manager == NULL) return;

    ResourceManager* const manager = *_manager;

    if (manager == NULL) return;

    if (manager->fonts != NULL) {
        for (unsigned int i = 0; i < manager->fontCount; i++) {
            TTF_CloseFont(manager->fonts[i]);
            manager->fonts[i] = NULL;
        }

        free(manager->fonts);
        manager->fonts = NULL;
    }

    free(manager);
    *_manager = NULL;

    TTF_Quit();
}


// Functions
void addResourceFont(ResourceManager* const manager, const char* const filename, const unsigned int size) {
    if (manager == NULL) return;

    unsigned int index = manager->fontCount;

    TTF_Font* font = TTF_OpenFont(filename, size);

    if (font == NULL) {
        exit(1);
    }

    size_t mSize = sizeof(TTF_Font*) * ++manager->fontCount;
    if (manager->fonts == NULL) {
        manager->fonts = (TTF_Font**) malloc(mSize);
    } else {
        manager->fonts = (TTF_Font**) realloc(manager->fonts, mSize);
    }

    if (manager->fonts == NULL) {
        exit(1);
    }

    manager->fonts[index] = font;
}

TTF_Font* getResourceFont(const ResourceManager* const manager, const char* const name) {
    if (manager == NULL) return NULL;

    for (unsigned int i = 0; i < manager->fontCount; i++) {
        TTF_Font* font = manager->fonts[i];

        char* filename = TTF_FontFaceFamilyName(font);

        if (strcmp(filename, name) == 0) {
            return font;
        }
    }

    return NULL;
}