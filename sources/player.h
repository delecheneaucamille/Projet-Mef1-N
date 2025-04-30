#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "card.h"

#define MIN_SIZE_HAND 20
#define MAX_SIZE_HAND 5

typedef struct
{
    int score;
    char *name;
    int ai;
    Card *hand;
    int sizeHand;
} Player;

void destructPlayer(Player *player);
Player *constuctPlayer();
void initPlayer(Player *p, int score, char *name, int ai, int sizeHand);
char *choiceName();
int selectSizeHand();

#endif