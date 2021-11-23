#pragma once

#include "../game.h"

typedef struct MainMenu _MainMenu;
typedef struct MenuChoice _MenuChoice;

struct MenuChoice {
    char* name;
    void (*action)(_MainMenu* const menu);
};

struct MainMenu {
    Game* game;

    _MenuChoice* menu_choices;
    unsigned int choice_amount;

    unsigned int current_choice;
};

typedef struct MainMenu MainMenu;
typedef struct MenuChoice MenuChoice;

MainMenu* createMainMenu(Game* const game);
void mainMenuAddChoice(MainMenu* const menu, const char* choiceName, void (*action)(MainMenu* const menu));
void destroyMainMenu(MainMenu** const menu);

void mainMenuMoveChoice(MainMenu* const menu, const int moveDirection);
void mainMenuActionChoice(MainMenu* const menu);

void updateMainMenu(MainMenu* const menu);
void renderMainMenu(SDL_Renderer* const renderer, const MainMenu* const menu);

static void _playGame(MainMenu* const menu);
static void _exitGame(MainMenu* const menu);