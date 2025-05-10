#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "card.h"
#include "player.h"

#define MAX_COLUMNS 4
#define MAX_ROWS 3
#define TIME_SLEEP 0.3

void displayPlayerCards(Player *players);
void displayCardWithName(Card *card, const char *name);
void displayLoading();

#endif
