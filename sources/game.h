#ifndef GAME_H
#define GAME_H

#include "card.h"
#include "ia.h"

// Définitions des constantes
#define MAX_PLAYERS 4
#define MIN_SIZE_HAND 5
#define MAX_SIZE_HAND 20
#define MAX_SIZE_STACK 15
#define MIN_SIZE_STACK -5
#define SIZE_STACK 100

// Déclaration anticipée de Player
typedef struct Player Player;

// Définition de la structure GameState
typedef struct
{
    Player **players;  // Tableau de pointeurs vers les joueurs
    int playerCount;   // Nombre de joueurs
    int currentPlayer; // Indice du joueur courant
    Discard *discard;  // Pile de défausse
    Stack *stack;      // Tas de cartes
} GameState;

// Prototypes des fonctions
GameState *initGame(Stack *stack, Discard *discard, int currentPlayer, int playerCount);
void destructGame(GameState *game);
void createPlayers(GameState *game, int aiCount);
int selectNbPlayers();
int selectNbAI(GameState *game);
void turnGame(GameState *game);
void return2RandomCards(GameState *game);
void distributeCards(GameState *game);
Player **calculateRanking(GameState *game);
void newGame();

#endif // GAME_H