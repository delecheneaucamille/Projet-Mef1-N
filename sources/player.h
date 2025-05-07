#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "card.h"

// Définitions des constantes
#define MIN_SIZE_HAND 20
#define MAX_SIZE_HAND 5

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

/**
 * @brief Libère la mémoire allouée pour un joueur.
 *
 * @param player Pointeur vers le joueur à détruire.
 */
void destructPlayer(Player *player);

/**
 * @brief Alloue dynamiquement un joueur.
 *
 * @return Player* Pointeur vers le joueur nouvellement créé.
 */
Player *constuctPlayer();

/**
 * @brief Initialise les attributs d'un joueur.
 *
 * @param p Pointeur vers le joueur.
 * @param score Score initial du joueur.
 * @param name Nom du joueur.
 * @param ai Indique si le joueur est une IA (1) ou un humain (0).
 * @param sizeHand Taille de la main du joueur.
 */
void initPlayer(Player *p, int score, char *name, int ai, int sizeHand);

/**
 * @brief Permet à l'utilisateur de choisir un nom.
 *
 * @return char* Pointeur vers le nom choisi.
 */
char *choiceName();

/**
 * @brief Génère aléatoirement la taille de la main d'un joueur.
 *
 * @return int Taille de la main.
 */
int selectSizeHand();

/**
 * Vérifie si toutes les cartes dans la main du joueur sont retournées (face visible).
 * 
 * @param player Pointeur vers le joueur dont on veut vérifier la main.
 * @return 1 si toutes les cartes sont retournées, 0 sinon.
 */
 void statehand(int *Player);

#endif // PLAYER_H