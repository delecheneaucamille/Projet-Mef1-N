#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "game.h"

// Définitions des constantes
#define MAX_COLUMNS 4
#define MAX_ROWS 3

// Déclaration anticipée de Player
typedef struct Player Player;

// Déclaration anticipée de Stack et Discard
typedef struct Stack Stack;
typedef struct Discard Discard;

// Prototypes des fonctions
void displayCardLine(Card c, int line);
void displayCards(Card **cards, int numberOfPlayers, int *cardsPerPlayer);
/**
 * @brief Affiche une carte avec son nom.
 *
 * @param card Pointeur vers la carte à afficher.
 * @param name Nom de la carte.
 */
void displayCardWithName(Card *card, const char *name);

#endif // DISPLAY_H