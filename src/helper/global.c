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
    const int endX = (int) point2.x + collision2.x;
    const int endY = (int) point2.y + collision2.y;

    if (horizontalDir != NULL) *horizontalDir = 0;
    if (verticalDir != NULL) *verticalDir = 0;

    if (startX < endX + collision2.w &&
        startX + collision1.w > endX &&
        startY < endY + collision2.h &&
        startY + collision1.h > endY) {
        /*
            TODO: Direction
        */

        return true;
    } else {
        return false;
    }
}