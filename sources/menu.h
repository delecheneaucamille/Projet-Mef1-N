#ifndef MENU_H
#define MENU_H

#include "game.h"

// Enumération pour les options du menu
typedef enum
{
    PLAY_VS_AI = 1,
    PLAY_VS_PLAYER,
    LOAD_GAME,
    SHOW_RULES,
    EXIT,
} MenuOption;

// Prototypes des fonctions du menu
void createMenu();
int choiceGame();
void selectGameMode();
void ranking(GameState *game);

#endif // MENU_H