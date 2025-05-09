#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "card.h"

// Définition de la structure Player
typedef struct
{
    int score;    // Score du joueur
    char *name;   // Nom du joueur
    int ai;       // 0 = joueur humain, 1 = joueur IA
    Card *hand;   // Main du joueur (tableau de cartes)
    int sizeHand; // Taille de la main
} Player;

void destructPlayer(Player *player);
Player *constructPlayer();
void initPlayer(Player *p, int score, char *name, int ai, int sizeHand);
char *choiceName();
int selectSizeHand();
void playerTurn(Player *p, Discard *d, Stack *s);

#endif // PLAYER_H