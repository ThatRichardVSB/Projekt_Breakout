#include <SDL.h>
#include <stdbool.h>

#include "../helper/global.h"
#include "menus/main_menu.h"
#include "environment/world.h"
#include "game.h"

static SDL_Event* current_events;
static unsigned int event_count;

static Point mouse_pos;

// Constructor / Deconstructor
Game* createGame(SDL_Renderer* const renderer, SDL_Window* const window, const SceneChoice start_scene) {
    Game* game = (Game*) malloc(sizeof(Game));

    if (game == NULL) {
        printf("No more memory!\n");
        exit(1);
    }

    game->renderer = renderer;
    game->window = window;

    game->quit = false;

    gameChangeScene(game, start_scene);

    return game;
}

void destroyGame(Game** const _game) {
    Game* const game = (Game* const) *_game;

    switch (game->scene.choice) {
        case MainMenuScene: {
            destroyMainMenu((MainMenu** const) &game->scene.source);
        } break;

        case WorldScene: {
            destroyWorld((World** const) &game->scene.source);
        } break;
    }

    free(game);
    *_game = NULL;

    free(current_events);
    current_events = NULL;
}


// Functions
void gameChangeScene(Game* const game, const SceneChoice choice) {
    game->scene.choice = choice;

    void* scene = NULL;

    switch (game->scene.choice) {
        case WorldScene: {
            scene = createWorld(game->window, NULL);
        } break;

        default: { // When invalid or Main, just go to the Main Menu
            scene = createMainMenu(game);
        }
    }

    game->scene.source = scene;
}


// Events
void eventGame(Game* const game, const SDL_Event event) {
    if (current_events == NULL) {
        current_events = (SDL_Event*) malloc(sizeof(SDL_Event));
    } else {
        current_events = (SDL_Event*) realloc(current_events, sizeof(SDL_Event) * (event_count + 1));
    }

    if (current_events == NULL) {
        printf("No more memory!\n");
        exit(1);
    }

    current_events[event_count] = event;

    event_count++;

    switch (event.type) {
        case SDL_MOUSEMOTION: {
            mouse_pos.x = event.motion.x;
            mouse_pos.y = event.motion.y;
        } break;

        case SDL_QUIT: {
            game->quit = true;
        } break;
    }
}

void eventClearGame(const Game* const game) {
    if (current_events == NULL) return;

    event_count = 0;

    free(current_events);
    current_events = NULL;
}

bool isKeyPressed(const SDL_Keycode key) {
    for (unsigned int i = 0; i < event_count; i++) {
        SDL_Event* event = &current_events[i];

        if (event->type == SDL_KEYDOWN) {
            if (event->key.keysym.sym == key) {
                return true;
            }
        }
    }

    return false;
}

Point getMousePos() {
    return mouse_pos;
}


// Update / Render
void updateGame(Game* const game, const double deltaTime) {
    switch (game->scene.choice) {
        case MainMenuScene: {
            updateMainMenu((MainMenu*) game->scene.source);
        } break;

        case WorldScene: {
            updateWorld((World*) game->scene.source, deltaTime);
        } break;
    }
}

void renderGame(const Game* const game) {
    switch (game->scene.choice) {
        case MainMenuScene: {
            renderMainMenu(game->renderer, (MainMenu*) game->scene.source);
        } break;

        case WorldScene: {
            renderWorld(game->renderer, (World*) game->scene.source);
        } break;
    }
}