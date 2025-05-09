#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>

// Définitions des constantes
#define SIZE_STACK 100
#define MIN_SIZE_STACK -5
#define MAX_SIZE_STACK 15

// Définition de la structure Card
typedef struct
{
    int value; // Valeur de la carte
    int state; // État de la carte (0 = face cachée, 1 = face visible, etc.)
} Card;

// Définition de la structure Stack
typedef struct
{
    int sizeStack; // Taille actuelle de la pile
    Card **stack;  // Tableau de pointeurs vers les cartes
} Stack;

// Définition de la structure Discard
typedef struct
{
    int indexLastCard; // Index de la dernière carte dans la pile
    Card **pile;       // Tableau de pointeurs vers les cartes dans le tas de défausse
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

#endif // CARD_H