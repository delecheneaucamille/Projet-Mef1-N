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
    int state; // État de la carte (0 = face cahée, 1 = face visible, etc.)
} Card;

// Définition de la structure Stack
typedef struct
{
    int sizeStack; // Taille actuelle de la pile
    Card **stack;  // Liste des cartes
} Stack;

// Définition de la structure Descard
typedef struct
{
    int indexLastCard;       // Index de la dernière carte dans la pile
    Card **pile[SIZE_STACK]; // Liste des cartes dans le tas de défausse
} Discard;

// Prototypes des fonctions pour Stack
Stack *initStack(int size, int min, int max);
void destructStack(Stack *stack);
void shuffleStack(Stack *stack);
Card *getCardFromStack(Stack *stack);
void printStack(Stack *stack);

// Prototypes des fonctions pour Descard
Discard *initDiscard();
void destructDiscard(Discard *d);
void addCardToDiscard(Discard *d, Card *c);
void removeLastCardFromDiscard(Discard *d);
Card *getLastCardFromDiscard(Discard *d);
void printDiscard(Discard *d);

// Prototypes des fonctions utilitaires
void selectCardValues(int *pmin, int *pmax);

#endif // CARD_H