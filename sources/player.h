#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "card.h"

// Définitions des constantes
#define MIN_SIZE_HAND 5
#define MAX_SIZE_HAND 20

// Déclaration anticipée de Discard et Stack
typedef struct Discard Discard;
typedef struct Stack Stack;

// Définition de la structure Player
typedef struct
{
    int score;    // Score du joueur
    char *name;   // Nom du joueur
    int ai;       // 0 = joueur humain, 1 = joueur IA
    Card *hand;   // Main du joueur (tableau de cartes)
    int sizeHand; // Taille de la main
} Player;

// Prototypes des fonctions
void destructPlayer(Player *player);
Player *constructPlayer();
void initPlayer(Player *p, int score, char *name, int ai, int sizeHand);
char *choiceName();
int selectSizeHand();
void playerTurn(Player *p, Discard *d, Stack *s);

#endif // PLAYER_H