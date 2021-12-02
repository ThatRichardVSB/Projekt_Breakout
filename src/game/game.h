#pragma once

#include <SDL.h>
#include <stdbool.h>

#include "../resources/resource_manager.h"
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

    ResourceManager* resources;

    Scene scene;

    bool quit;
} Game;

Game* createGame(SDL_Renderer* const renderer, SDL_Window* const window, ResourceManager* const resources, const SceneChoice start_scene);
void destroyGame(Game** const game);

void gameChangeScene(Game* const game, const SceneChoice choice);

void eventGame(Game* const game, const SDL_Event event);
void eventClearGame(const Game* const game);
bool isKeyPressed(const SDL_Keycode key);
bool isMousePressed(const int button);
Point getMousePos();

void updateGame(Game* const game, const double deltaTime);
void renderGame(const Game* const game);