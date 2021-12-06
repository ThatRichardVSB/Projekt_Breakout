#pragma once

#include <SDL.h>
#include <stdbool.h>

#include "../resources/resource_manager.h"
#include "../helper/global.h"
#include "game.h"

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;

    ResourceManager* resources;

    void* world;

    int argc;
    char** argv;

    bool quit;
} Game;

Game* createGame(SDL_Renderer* const renderer, SDL_Window* const window, ResourceManager* const resources, int argc, char** argv);
void destroyGame(Game** const game);

void eventGame(Game* const game, const SDL_Event event);
void eventClearGame();
bool isKeyPressed(const SDL_Keycode key);
bool isKeyJustPressed(const SDL_Keycode key);
bool isMousePressed(const int button);
Point getMousePos();

void updateGame(Game* const game, const double deltaTime);
void renderGame(const Game* const game);