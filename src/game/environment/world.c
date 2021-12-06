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
World* createWorld(Game* const game, char* const mapFilename) {
    World* world = (World*) malloc(sizeof(World));

    if (world == NULL) {
        exit(1);
    }

    int win_h = 0;
    SDL_GetWindowSize(game->window, NULL, &win_h);

    world->game = game;
    world->ball = NULL;
    world->map = createMap(game->window, mapFilename);
    world->paddle = createPaddle((world->map->width * BLOCK_WIDTH + WALL_WIDTH) / 2, win_h - (PADDLE_BOTTOM_BLOCK_MARGIN * BLOCK_HEIGHT), world->map->walls);

    world->points = 0;
    world->turns = MAX_TURNS;
    world->screensLeft = MAX_SCREENS;

    world->state = Idle;

    world->statsFont = getResourceFont(world->game->resources, "Arial");

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
    generateMap(world->map);
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
        if (isMousePressed(SDL_BUTTON_LEFT) || isKeyJustPressed(SDLK_SPACE)) {
            if (world->state == Idle) {
                launchBallWorld(world);

                world->state = Playing;
            } else { // When Lost or Won you have to click once to return to Idle
                if (world->state == Won || world->state == Lost) {
                    resetWorld(world);
                }

                world->state = Idle;
            }
        }
    }

    Block destroyedBlock = Air; // Air = no block destroyed
    updateBall(world->ball, world->map, world->paddle, &destroyedBlock, deltaTime);
    world->points += destroyedBlock;

    if (world->state == Playing) { // Game is being played
        int win_h = 0;
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
            world->screensLeft--;

            if (world->screensLeft > 0) {
                generateMap(world->map);
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

    char str[100];
    sprintf(str, "Score: %d Balls: %d Maps: %d", world->points, world->turns, world->screensLeft);

    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(world->statsFont,
        str,
        color
    );
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int w, h;
    TTF_SizeText(world->statsFont, str, &w, &h);
    float hRatio = (float) w / h, wRatio = (float) h / w;

    const int maxW = world->map->width * BLOCK_WIDTH;
    const int maxH = (world->map->walls[1].y + world->map->walls[1].h - (WALL_WIDTH * 2));

    if (w > h) {
        if (w > maxW) {
            w = maxW;
            h = w * wRatio;
        }

        if (h > maxH) {
            h = maxH;
            w = h * hRatio;
        }
    } else {
        if (h > maxH) {
            h = maxH;
            w = h * hRatio;
        }

        if (w > maxW) {
            w = maxW;
            h = w * wRatio;
        }
    }

    SDL_Rect txt_pos = {
        .x = world->map->walls[0].x + world->map->walls[0].w,
        .y = world->map->walls[1].y + WALL_WIDTH,
        .w = w,
        .h = h
    };

    SDL_RenderCopy(renderer, texture, NULL, &txt_pos);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}