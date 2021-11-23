#pragma once

#include <SDL.h>
#include <stdbool.h>

#include "../helper/global.h"
#include "game.h"

typedef enum {
    MainMenuScene,
    WorldScene
} SceneChoice;

typedef struct {
    SceneChoice choice;
    void* source;
} Scene;

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;

    Scene scene;
} Game;

Game* createGame(SDL_Renderer* renderer, SDL_Window* window, SceneChoice start_scene);
void destroyGame(Game** game);

void gameChangeScene(Game* game, SceneChoice choice);

void eventGame(Game* game, SDL_Event event);
void eventClearGame(Game* game);
bool isKeyPressed(SDL_Keycode key);
Point getMousePos();

void updateGame(Game* game);
void renderGame(Game* game);