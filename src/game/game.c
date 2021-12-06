#include <SDL.h>
#include <stdbool.h>

#include "../helper/global.h"
#include "environment/world.h"
#include "../resources/resource_manager.h"
#include "game.h"

static SDL_Event* current_events = NULL;
static unsigned int event_count = 0;

static SDL_Keycode* keys_pressed = NULL;
static SDL_Keycode* keys_just_pressed = NULL;
static unsigned int key_count = 0;
static unsigned int just_key_count = 0;

static Point mouse_pos = {
    .x = 0,
    .y = 0
};

// Constructor / Deconstructor
Game* createGame(SDL_Renderer* const renderer, SDL_Window* const window, ResourceManager* const resources, int argc, char** argv) {
    Game* game = (Game*) malloc(sizeof(Game));

    if (game == NULL) {
        exit(1);
    }

    game->renderer = renderer;
    game->window = window;
    game->resources = resources;

    game->quit = false;

    game->argc = argc;
    game->argv = argv;

    char* map = NULL;
    if (game->argc >= 2) {
        map = game->argv[1];
    }

    game->world = createWorld(game, map);

    return game;
}

void destroyGame(Game** const _game) {
    if (_game == NULL) return;

    Game* const game = *_game;

    if (game == NULL) return;

    destroyWorld((World** const) &game->world);

    destroyResourceManager(&game->resources);

    free(game);
    *_game = NULL;

    free(current_events);
    current_events = NULL;
}


// Events
void eventGame(Game* const game, const SDL_Event event) {
    if (current_events == NULL) {
        current_events = (SDL_Event*) malloc(sizeof(SDL_Event));
    } else {
        current_events = (SDL_Event*) realloc(current_events, sizeof(SDL_Event) * (event_count + 1));
    }

    if (current_events == NULL) {
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

        case SDL_KEYDOWN: {
            bool found = false;
            for (unsigned int i = 0; i < key_count; i++) {
                if (keys_pressed[i] == event.key.keysym.sym) {
                    found = true;
                }
            }

            if (!found) {
                unsigned int index = key_count;
                unsigned int justIndex = just_key_count;
                size_t mSize = sizeof(SDL_Keycode) * ++key_count;
                size_t mJustSize = sizeof(SDL_Keycode) * ++just_key_count;

                if (keys_pressed == NULL) {
                    keys_pressed = (SDL_Keycode*) malloc(mSize);
                } else {
                    keys_pressed = (SDL_Keycode*) realloc(keys_pressed, mSize);
                }

                if (keys_pressed == NULL) {
                    exit(1);
                }

                if (keys_just_pressed == NULL) {
                    keys_just_pressed = (SDL_Keycode*) malloc(mJustSize);
                } else {
                    keys_just_pressed = (SDL_Keycode*) realloc(keys_just_pressed, mJustSize);
                }

                if (keys_pressed == NULL) {
                    exit(1);
                }

                keys_pressed[index] = event.key.keysym.sym;
                keys_just_pressed[justIndex] = event.key.keysym.sym;
            }
        } break;

        case SDL_KEYUP: {
            for (unsigned int i = 0; i < key_count; i++) {
                if (keys_pressed[i] == event.key.keysym.sym) {
                    for (unsigned int j = i; j < key_count - 1; j++) {
                        keys_pressed[j] = keys_pressed[j + 1];
                    }

                    size_t mSize = sizeof(SDL_Keycode) * --key_count;

                    if (mSize <= 0) {
                        free(keys_pressed);
                        keys_pressed = NULL;
                    } else {
                        keys_pressed = (SDL_Keycode*) realloc(keys_pressed, mSize);

                        if (keys_pressed == NULL) {
                            exit(1);
                        }
                    }

                    break;
                }
            }
        } break;
    }
}

void eventClearGame(const Game* const game) {
    if (current_events == NULL) return;

    event_count = 0;

    free(current_events);
    current_events = NULL;

    free(keys_just_pressed);
    keys_just_pressed = NULL;

    just_key_count = 0;
}

bool isKeyPressed(const SDL_Keycode key) {
    for (unsigned int i = 0; i < key_count; i++) {
        if (keys_pressed[i] == key) {
            return true;
        }
    }

    return false;
}

bool isKeyJustPressed(const SDL_Keycode key) {
    for (unsigned int i = 0; i < just_key_count; i++) {
        if (keys_just_pressed[i] == key) {
            return true;
        }
    }

    return false;
}

bool isMousePressed(const int button) {
    for (unsigned int i = 0; i < event_count; i++) {
        SDL_Event* event = &current_events[i];

        if (event->type == SDL_MOUSEBUTTONDOWN) {
            if (event->button.button == button) {
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
    if (game == NULL) return;

    updateWorld((World*) game->world, deltaTime);
}

void renderGame(const Game* const game) {
    if (game == NULL) return;

    renderWorld(game->renderer, (World*) game->world);
}