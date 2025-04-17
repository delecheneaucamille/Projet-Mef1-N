#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>

#define SIZE_STACK 100
#define MIN -5
#define MAX 15

typedef struct
{
    int value;
    int state;
} Card;

void destructStack(Card **stackCard, int size);
void shuffleStack(Card **stackCard, int size);
void selectValuesCard(int *pmin, int *pmax);
void initStack(Card **stackCard, int size, int min, int max);
void printStack(Card **stackCard, int size);

#endif