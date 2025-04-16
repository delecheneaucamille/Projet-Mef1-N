#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_STACK 100

typedef struct
{
    int value;
    int state;
} Card;

void shuffleStack(int *stackCarte, int size);

#endif