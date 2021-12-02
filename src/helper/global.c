#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL_ttf.h>

#include "global.h"

// Constructors / Deconstructors
CollisionBox createCollision(const int x, const int y, const unsigned int w, const unsigned int h) {
    CollisionBox collision = {
        .x = x,
        .y = y,
        .w = w,
        .h = h
    };

    return collision;
}

bool isColliding(const Point p1, const CollisionBox col1, const Point p2, const CollisionBox col2, int* const horDir, int* const verDir) {
    const int startX = (int) p1.x + col1.x;
    const int startY = (int) p1.y + col1.y;
    const int startEndX = startX + col1.w;
    const int startEndY = startY + col1.h;

    const int endX = (int) p2.x + col2.x;
    const int endY = (int) p2.y + col2.y;
    const int endEndX = endX + col2.w;
    const int endEndY = endY + col2.h;

    if (startX < endEndX &&
        startEndX > endX &&
        startY < endEndY &&
        startEndY > endY) {

        unsigned int diffX = 0;
        unsigned int diffY = 0;
        int dirX = 0;
        int dirY = 0;

        if (startX < endX) {
            diffX = endX - startX;

            if (diffX != 0) dirX = -1;
        } else if (startEndX > endEndX) {
            diffX = startEndX - endEndX;

            if (diffX != 0) dirX = 1;
        }

        if (startY < endY) {
            diffY = endY - startY;

            if (diffY != 0) dirY = -1;
        } else if (startEndY > endEndY) {
            diffY = startEndY - endEndY;

            if (diffY != 0) dirY = 1;
        }

        if (diffX > diffY && horDir != NULL) {
            *horDir = dirX;
        } else if (diffY > diffX && verDir != NULL) {
            *verDir = dirY;
        } else if (diffX == diffY && horDir != NULL && verDir != NULL) {
            *horDir = dirX;
            *verDir = dirY;
        }

        return true;
    } else {
        return false;
    }
}