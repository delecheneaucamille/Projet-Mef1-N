#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "card.h"

typedef struct
{
    int score;
    char *name;
    int ai;
    Card **hand;
    int sizeHand;
} Player;

void destructPlayer(Player *player);
Player *constructPlayer();
void initPlayer(Player *p, int score, char *name, int ai, int sizeHand);
char *choiceName();
int selectSizeHand();
void playerTurn(Player *p, Discard *d, Stack *s);

#endif