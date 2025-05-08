#ifndef IA_H
#define IA_H

#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "card.h"

// Prototypes des fonctions

/**
 * @brief Retourne l'index de la carte ayant la valeur la plus élevée dans la main d'un joueur IA.
 *
 * @param p Pointeur vers le joueur IA.
 * @return int Index de la carte ayant la valeur la plus élevée, ou -1 si la main est vide.
 */
int getIndexHighestCard(Player *p);

/**
 * @brief Change l'état de la première carte non retournée (state = 0) dans la main d'un joueur IA.
 *
 * @param p Pointeur vers le joueur IA.
 */
void turnStateCard(Player *p);

/**
 * @brief Effectue le tour de jeu d'un joueur IA.
 *
 * @param p Pointeur vers le joueur IA.
 * @param s Pointeur vers le tas de cartes.
 * @param d Pointeur vers la pile de défausse.
 */
void iaTurn(Player *p, Stack *s, Discard *d);

#endif // IA_H