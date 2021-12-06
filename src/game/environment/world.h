#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "map.h"
#include "../player/ball.h"
#include "../player/paddle.h"
#include "../game.h"

#define PADDLE_BOTTOM_BLOCK_MARGIN 2
#define MAX_TURNS 3
#define MAX_SCREENS 2

typedef enum {
    Idle,
    Playing,
    Lost,
    Won
} WorldState;

typedef struct {
    Map* map;
    Paddle* paddle;
    Ball* ball;

    int points;
    int turns;
    int screensLeft;

    WorldState state;

    Game* game;
    TTF_Font* statsFont;
} World;

World* createWorld(Game* const game, char* const mapFilename);
void destroyWorld(World** const world);

void launchBallWorld(World* const world);
void resetWorld(World* const world);

void updateWorld(World* const world, const double deltaTime);
void renderWorld(SDL_Renderer* const renderer, const World* const world);