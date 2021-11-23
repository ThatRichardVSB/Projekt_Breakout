#pragma once

#include "../game.h"

typedef struct MainMenu _MainMenu;
typedef struct MenuChoice _MenuChoice;

struct MenuChoice {
    char* name;
    void (*action)(_MainMenu* menu);
};

struct MainMenu {
    Game* game;

    _MenuChoice* menu_choices;
    unsigned int choice_amount;

    unsigned int current_choice;
};

typedef struct MainMenu MainMenu;
typedef struct MenuChoice MenuChoice;

MainMenu* createMainMenu(Game* game);
void mainMenuAddChoice(MainMenu* menu, char* choiceName, void (*action)(MainMenu* menu));
void destroyMainMenu(MainMenu** menu);

void mainMenuMoveChoice(MainMenu* menu, int moveDirection);
void mainMenuActionChoice(MainMenu* menu);

void updateMainMenu(MainMenu* menu);
void renderMainMenu(SDL_Renderer* renderer, MainMenu* menu);

static void _playGame(MainMenu* menu);
static void _exitGame(MainMenu* menu);