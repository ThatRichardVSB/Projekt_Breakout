#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>

#include "../game.h"
#include "world.h"
#include "map.h"
#include "../../helper/global.h"
#include "../player/ball.h"
#include "../player/paddle.h"
#include "../../resources/resource_manager.h"

TTF_Font* font;

// Constructor / Deconstructor
World* createWorld(Game* const game, FILE* const mapFile) {
    World* world = (World*) malloc(sizeof(World));

    if (world == NULL) {
        exit(1);
    }

    unsigned win_h = 0;
    SDL_GetWindowSize(game->window, NULL, &win_h);

    world->game = game;
    world->ball = NULL;
    // TODO: Map file
    world->map = createMap(game->window, mapFile);
    world->paddle = createPaddle((world->map->width * BLOCK_WIDTH + WALL_WIDTH) / 2, win_h - (PADDLE_BOTTOM_BLOCK_MARGIN * BLOCK_HEIGHT), world->map->walls);

    world->points = 0;
    world->turns = MAX_TURNS;
    world->screensLeft = MAX_SCREENS;

    world->state = Idle;

    return world;
}

void destroyWorld(World** const _world) {
    if (_world == NULL) return;

    World* const world = *_world;

    if (world == NULL) return;

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
    updatePaddle(world->paddle, deltaTime);

    if (world->state != Playing) { // Game hasn't started yet
        if (isMousePressed(SDL_BUTTON_LEFT) || isKeyPressed(SDLK_SPACE)) {
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

        if (world->ball->position.y > win_h + BALL_RADIUS) { // When the ball goes below the screen
            world->state = Idle;

            destroyBall(&world->ball);

            world->turns--;

            if (world->turns <= 0) {
                world->state = Lost;

                resetWorld(world);
            }
        }

        if (destroyedBlock != Air && getBlockCountMap(world->map) == 0) { // When no blocks are on the map anymore
            if (world->screensLeft > 0) {
                world->screensLeft--;

                generateMap(world->map, NULL);
                launchBallWorld(world);
            } else {
                world->state = Won;
            }
        }
    }
}

void renderWorld(SDL_Renderer* const renderer, const World* const world) {
    if (world == NULL) return;

    renderBall(renderer, world->ball);
    renderPaddle(renderer, world->paddle);
    renderMap(renderer, world->map);

    TTF_Font* font = getResourceFont(world->game->resources, "Arial");

    // TODO: Print stats
    /*if (font != NULL) {
        SDL_Color color = { 255, 255, 255 };
        SDL_Surface* surface = TTF_RenderText_Solid(font,
            "Welcome to Gigi Labs", color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }*/
}