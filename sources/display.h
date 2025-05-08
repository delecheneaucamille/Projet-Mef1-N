#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "card.h"

// Définitions des constantes
#define MAX_COLUMNS 4
#define MAX_ROWS 3

// Prototypes des fonctions
void displayCardLine(Card c, int line);
void displayCards(Card **cards, int numberOfPlayers, int *cardsPerPlayer);
/**
 * @brief Affiche une carte avec son nom.
 *
 * @param card Pointeur vers la carte à afficher.
 * @param name Nom de la carte.
 */
void displayCardWithName(Card *card, const char *name)

#endif // DISPLAY_H