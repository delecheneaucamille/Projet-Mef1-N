#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "card.h"
#include "ia.h"

// Définitions des constantes
#define MAX_PLAYERS 4
#define MIN_SIZE_HAND 5
#define MAX_SIZE_HAND 20
#define MAX_SIZE_STACK 15
#define MIN_SIZE_STACK -5
#define SIZE_STACK 100

// Définition de la structure GameState
typedef struct
{
    Player **players;  // Liste des joueurs
    int playerCount;   // Nombre de joueurs
    int currentPlayer; // Indice du joueur courant
    Discard *discard;  // Pile de défausse
    Stack *stack;      // Tas de cartes
} GameState;

// Prototypes des fonctions

/**
 * @brief Initialise l'état du jeu.
 *
 * @param stack Pointeur vers le tas de cartes.
 * @param discard Pointeur vers la pile de défausse.
 * @param currentPlayer Indice du joueur courant.
 * @param playerCount Nombre de joueurs.
 * @return GameState* Pointeur vers l'état du jeu initialisé.
 */
GameState *initGame(Stack *stack, Discard *discard, int currentPlayer, int playerCount);

/**
 * @brief Libère la mémoire allouée pour l'état du jeu.
 *
 * @param game Pointeur vers l'état du jeu à détruire.
 */
void destructGame(GameState *game);

/**
 * @brief Crée les joueurs pour le jeu.
 *
 * @param game Pointeur vers l'état du jeu.
 * @param aiCount Nombre de joueurs IA.
 */
void createPlayers(GameState *game, int aiCount);

/**
 * @brief Sélectionne le nombre de joueurs.
 *
 * @return int Nombre de joueurs sélectionné.
 */
int selectNbPlayers();

/**
 * @brief Sélectionne le nombre de joueurs IA.
 *
 * @param game Pointeur vers l'état du jeu.
 * @return int Nombre de joueurs IA sélectionné.
 */
int selectNbAI(GameState *game);

/**
 * @brief Gère le déroulement du jeu.
 *
 * @param game Pointeur vers l'état du jeu.
 */
void turnGame(GameState *game);

/**
 * @brief Retourne deux cartes aléatoires pour chaque joueur.
 *
 * @param game Pointeur vers l'état du jeu.
 */
void return2RandomCards(GameState *game);

/**
 * @brief Distribue les cartes aux joueurs.
 *
 * @param game Pointeur vers l'état du jeu.
 */
void distributeCards(GameState *game);

/**
 * @brief lance une animation de chargement
 */
void displayLoading();

/**
 * @brief Vérifie si un joueur a terminé la partie.
 *
 * @param player Pointeur vers le joueur.
 * @return int 1 si toutes les cartes sont retournées, 0 sinon.
 */
int checkEndGame(Player *player);

/**
 * @brief Calcule le classement final des joueurs.
 *
 * @param game Pointeur vers l'état du jeu.
 * @return Player* Tableau des joueurs triés par score.
 */
Player *calculateRanking(GameState *game);

/**
 * @brief Lance une nouvelle partie.
 */
void newGame();

#endif // GAME_H