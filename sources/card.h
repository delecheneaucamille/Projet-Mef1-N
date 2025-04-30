#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>

#define SIZE_STACK 100
#define MIN_SIZE_STACK -5
#define MAX_SIZE_STACK 15

typedef struct
{
    int value;
    int state;
} Card;

typedef struct
{
    int indexLastCard;
    Card **pile[SIZE_STACK];
} Descard;

void destructStack(Card **stackCard, int size);
void shuffleStack(Card **stackCard, int size);
void selectCardValues(int *pmin, int *pmax);
void initStack(Card **stackCard, int size, int min, int max);
void printStack(Card **stackCard, int size);
Descard *initDescard();
void destructDescard(Descard *d);
Card *getLastCardToDescard(Descard *d, int index);
void printDescard(Descard *d);

#endif