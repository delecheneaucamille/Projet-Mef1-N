#include <stdio.h>
#include <stdlib.h>
#include <card.h>
#include <player.h>
#include <game.h>

#define MAX_COLONNES 4
#define MAX_LIGNES 3



void afficherCarteLigne(Card c, int ligne) {
    switch (ligne) {
        case 0: printf("╔═══╗"); break;
        case 1:
            if (c.state == 1)
                printf("║%3d║", c.value);
            else
                printf("║ ??║");
            break;
        case 2: printf("╚═══╝"); break;
    }
}

void afficherCartes(Card **cartes, int nbofplayer, int *nbCardByPlayer) {
    for (int joueur = 0; joueur < nbofplayer; joueur++) {
        printf("=========== Joueur %d ===========\n", joueur + 1);
        int nbCartes = nbCardByPlayer[joueur];
        int lignes = (nbCartes + MAX_COLONNES - 1) / MAX_COLONNES;

        for (int ligneCarte = 0; ligneCarte < lignes; ligneCarte++) {
            for (int h = 0; h < 3; h++) { // hauteur de chaque carte
                for (int col = 0; col < MAX_COLONNES; col++) {
                    int index = ligneCarte * MAX_COLONNES + col;
                    if (index < nbCartes) {
                        afficherCarteLigne(cartes[joueur][index], h);
                        printf(" ");
                    } else {
                        printf("       ");
                    }
                }
                printf("\n");
            }
        }
        printf("\n");
    }
}


int main() {
    int nbofplayer = 3;
    int nbCardByPlayer[] = {12, 9, 6};

    // Allocation dynamique
    Card **cartes = malloc(nbofplayer * sizeof(Card *));
    for (int i = 0; i < nbofplayer; i++) {
        cartes[i] = malloc(nbCardByPlayer[i] * sizeof(Card));
        for (int j = 0; j < nbCardByPlayer[i]; j++) {
            cartes[i][j].value = rand() % 13 - 2; // [-2, 10]
            cartes[i][j].state = rand() % 2;        // 0 ou 1
        }
    }

    afficherCartes(cartes, nbofplayer, nbCardByPlayer);

    for (int i = 0; i < nbofplayer; i++) {
        free(cartes[i]);
    }
    free(cartes);

    return 0;
}
