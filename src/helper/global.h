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
bool isColliding(const Point p1, const CollisionBox col1, const Point p2, const CollisionBox col2, int* const horDir, int* const verDir);