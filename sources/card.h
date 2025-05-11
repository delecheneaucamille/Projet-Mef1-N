#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>

#define SIZE_STACK 400
#define MIN_CARDS_VALUES -5
#define MAX_CARDS_VALUES 15

typedef struct
{
    int value;
    int state;
} Card;

typedef struct
{
    int sizeStack;
    Card **stack;
} Stack;

typedef struct
{
    int indexLastCard;
    Card **pile;
} Discard;

void destructStack(Stack *stack);
void shuffleStack(Stack *stack);
void selectCardValues(int *pmin, int *pmax);
Stack *initStack(int size, int min, int max);
Card *getCardFromStack(Stack *stack);
void addCardToDiscard(Discard *d, Card *c);
void removeLastCardFromDiscard(Discard *d);
Card *getLastCardFromDiscard(Discard *d);
Discard *initDiscard();
void destructDiscard(Discard *d);

#endif
