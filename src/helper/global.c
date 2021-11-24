#include <stdlib.h>
#include <stdbool.h>

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

bool isColliding(Point point1, CollisionBox collision1, Point point2, CollisionBox collision2, int* horizontalDir, int* verticalDir) {
    const int startX = (int) point1.x + collision1.x;
    const int startY = (int) point1.y + collision1.y;
    const int startEndX = startX + collision1.w;
    const int startEndY = startY + collision1.h;

    const int endX = (int) point2.x + collision2.x;
    const int endY = (int) point2.y + collision2.y;
    const int endEndX = endX + collision2.w;
    const int endEndY = endY + collision2.h;

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

        if (diffX > diffY && horizontalDir != NULL) {
            *horizontalDir = dirX;
        } else if (diffY > diffX && verticalDir != NULL) {
            *verticalDir = dirY;
        } else if (diffX == diffY && horizontalDir != NULL && verticalDir != NULL) {
            *horizontalDir = dirX;
            *verticalDir = dirY;
        }

        return true;
    } else {
        return false;
    }
}