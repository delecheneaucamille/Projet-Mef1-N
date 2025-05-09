#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "card.h"
#include "player.h"

// Définitions des constantes
#define MAX_COLUMNS 4
#define MAX_ROWS 3

// Prototypes des fonctions
void displayPlayerCards(Player *players);
void displayCardWithName(Card *card, const char *name);

#endif // DISPLAY_H