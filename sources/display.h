#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "card.h"

// Définitions des constantes
#define MAX_COLUMNS 4
#define MAX_ROWS 3

// Prototypes des fonctions
void displayCardLine(Card c, int line);
void displayCards(Player *players, int playerCount);

#endif // DISPLAY_H