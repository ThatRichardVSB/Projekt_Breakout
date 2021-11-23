#pragma once

#include <stdbool.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    int x;
    int y;
    unsigned int w;
    unsigned int h;
} CollisionBox;

CollisionBox createCollision(const int x, const int y, const unsigned int w, const unsigned int h);
bool isColliding(Point point1, CollisionBox collision1, Point point2, CollisionBox collision2, int* horizontalDir, int* verticalDir);