#include <SDL.h>
#include <stdlib.h>

#include "../game.h"
#include "world.h"
#include "map.h"
#include "../../helper/global.h"
#include "../player/ball.h"
#include "../player/paddle.h"


// Constructor / Deconstructor
World* createWorld(Game* const game, FILE* const mapFile) {
    World* world = (World*) malloc(sizeof(World));

    if (world == NULL) {
        printf("No more memory!\n");
        exit(1);
    }

    unsigned win_h = 0;
    SDL_GetWindowSize(game->window, NULL, &win_h);

    world->game = game;
    world->map = createMap(game->window, mapFile);
    world->paddle = createPaddle(0, 0, win_h - (PADDLE_BOTTOM_BLOCK_MARGIN * BLOCK_HEIGHT));

    world->points = 0;
    world->turns = MAX_TURNS;
    world->screensLeft = MAX_SCREENS;

    world->state = Idle;

    return world;
}

void destroyWorld(World** const _world) {
    if (_world == NULL) return;

    World* world = *_world;

    destroyBall(&world->ball);
    destroyPaddle(&world->paddle);
    destroyMap(&world->map);

    free(world);
    *_world = NULL;
}


// Functions
void launchBallWorld(World* const world) {
    world->state = Playing;

    if (world->ball != NULL) {
        destroyBall(&world->ball);
    }

    world->ball = createBall(world->paddle->position.x, world->paddle->position.y - BALL_SPAWN_HEIGHT, BALL_SPEED, BALL_RADIUS);
}

void resetWorld(World* const world) {
    generateMap(world->map, NULL);
    destroyBall(&world->ball);

    world->points = 0;
    world->turns = MAX_TURNS;
    world->screensLeft = MAX_SCREENS;
}


// Update / Render
void updateWorld(World* const world, const double deltaTime) {
    if (world == NULL) return;

    updateMap(world->map);
    updatePaddle(world->paddle);

    if (world->state != Playing) { // Game hasn't started yet
        if (isMousePressed(SDL_BUTTON_LEFT)) {
            if (world->state == Idle) {
                launchBallWorld(world);

                world->state = Playing;
            } else { // When Lost or Won you have to click once to return to Idle
                world->state = Idle;
            }
        }
    }

    Block destroyedBlock = Air; // Air = no block destroyed
    updateBall(world->ball, world->map, world->paddle, &destroyedBlock, deltaTime);
    world->points += destroyedBlock;

    if (world->state == Playing) { // Game is being played
        unsigned int win_h = 0;
        SDL_GetWindowSize(world->game->window, NULL, &win_h);

        if (world->ball->position.y > win_h + BALL_RADIUS) {
            world->state = Idle;

            destroyBall(&world->ball);

            world->turns--;
        }
    }

    if (getBlockCountMap(world->map) == 0) {
        if (world->screensLeft > 0) {
            world->screensLeft--;

            generateMap(world->map, NULL);
            launchBallWorld(world);
        } else {
            world->state = Won;
        }
    } else if (world->turns <= 0) {
        world->state = Lost;

        resetWorld(world);
    }

    system("clear");
    printf("State: %d\n", world->state);
    printf("Points: %d\tTurns: %d\tScreens: %d\n", world->points, world->turns, world->screensLeft);
}

void renderWorld(SDL_Renderer* const renderer, const World* const world) {
    if (world == NULL) return;

    renderBall(renderer, world->ball);
    renderPaddle(renderer, world->paddle);
    renderMap(renderer, world->map);
}