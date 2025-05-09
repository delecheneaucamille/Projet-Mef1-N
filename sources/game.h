#ifndef GAME_H
#define GAME_H

#include "card.h"
#include "player.h"

// Définition de la structure GameState
typedef struct
{
    Player **players;  // Tableau de pointeurs vers les joueurs
    int playerCount;   // Nombre de joueurs
    int currentPlayer; // Indice du joueur courant
    Discard *discard;  // Pile de défausse
    Stack *stack;      // Tas de cartes
} GameState;

void newGame();

#endif // GAME_H