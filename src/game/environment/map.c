#include <stdlib.h>
#include "map.h"


// Constructor / Deconstructor
Map* createMap(FILE* mapFile) {
    Map* map = (Map*) malloc(sizeof(Map));

    if (map == NULL) {
        exit(-1);
    }

    return map;
}

void destroyMap(Map** map) {
    free(*map);
    *map = NULL;
}


// Update / Render
void updateMap(Map* map) {

}

void renderMap(SDL_Renderer* renderer, Map* map) {

}