#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "game.h"
#include "card.h"
#include "player.h"
// github publiques

int main()
{
    // Initialisation du jeu
    printf("Bienvenue dans le jeu de cartes Skyjo !\n");
    printf("Chargement des ressources...\n");

    // Affichage du menu principal
    createMenu();

    // Sélection du mode de jeu
    selectGameMode();

    // Fin du programme
    printf("Merci d'avoir joué ! À bientôt.\n");
    return 0;
}