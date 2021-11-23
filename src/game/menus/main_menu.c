#include <stdlib.h>
#include <string.h>

#include "main_menu.h"
#include "../game.h"


// Constructor / Deconstructor
MainMenu* createMainMenu(Game* const game) {
    MainMenu* menu = (MainMenu*) malloc(sizeof(MainMenu));

    menu->game = game;

    menu->menu_choices = NULL;
    menu->choice_amount = 0;
    menu->current_choice = 0;

    mainMenuAddChoice(menu, "Play", _playGame);
    mainMenuAddChoice(menu, "Exit", _exitGame);

    return menu;
}

void mainMenuAddChoice(MainMenu* const menu, const char* choiceName, void (*action)(MainMenu* const menu)) {
    unsigned int index = menu->choice_amount;

    menu->choice_amount++;

    if (menu->menu_choices == NULL) {
        menu->menu_choices = (MenuChoice*) malloc(sizeof(MenuChoice) * menu->choice_amount);
    } else {
        menu->menu_choices = (MenuChoice*) realloc(menu->menu_choices, sizeof(MenuChoice) * menu->choice_amount);
    }

    MenuChoice choice;

    choice.name = (char*) malloc(sizeof(char) * strlen(choiceName));
    strcpy(choice.name, choiceName);

    choice.action = action;

    menu->menu_choices[index] = choice;
}

void destroyMainMenu(MainMenu** const _menu) {
    MainMenu* menu = (MainMenu* const) *_menu;

    for (unsigned int i = 0; i < menu->choice_amount; i++) {
        free(menu->menu_choices[i].name);
    }
    free(menu->menu_choices);
    free(menu);
    *_menu = NULL;
}


// Functions
void mainMenuMoveChoice(MainMenu* const menu, const int moveDirection) {
    if (moveDirection < 0) {
        menu->current_choice--;
    } else if (moveDirection > 0) {
        menu->current_choice++;
    }

    if (menu->current_choice >= menu->choice_amount) {
        menu->current_choice = 0;
    } else if (menu->current_choice < 0) {
        menu->current_choice = menu->choice_amount - 1;
    }
}

void mainMenuActionChoice(MainMenu* const menu) {
    menu->menu_choices[menu->current_choice].action(menu);
}


// Update / Render
void updateMainMenu(MainMenu* const menu) {

}

void renderMainMenu(SDL_Renderer* const renderer, const MainMenu* const menu) {

}


// Choice function definitions
static void _playGame(MainMenu* const menu) {
    gameChangeScene(menu->game, WorldScene);
}

static void _exitGame(MainMenu* const menu) {
    menu->game->quit = true;
}