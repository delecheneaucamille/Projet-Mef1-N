#ifndef GAME_H
#define GAME_H

#include "card.h"
#include "player.h"

typedef struct
{
    Player **players;
    int playerCount;
    int currentPlayer;
    Discard *discard;
    Stack *stack;
} GameState;

void newGame();

#endif