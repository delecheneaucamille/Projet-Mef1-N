#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "player.h"
#include "game.h"
#include "colors.h"

#define MAX_COLUMNS 4
#define MAX_ROWS 3

void displayCardLine(Card c, int line)
{
    switch (line)
    {
    case 0:
        printf("\033[34m╔═══╗\033[0m"); // Bordure en bleu
        break;
    case 1:
        if (c.state == 1)                            // Carte visible
            printf("\033[35m║%3d║\033[0m", c.value); // Chiffre en magenta
        else                                         // Carte cachée
            printf("\033[34m║ ??║\033[0m");          // Texte en bleu
        break;
    case 2:
        printf("\033[34m╚═══╝\033[0m"); // Bordure en bleu
        break;
    }
}

void displayCards(Player *players, int playerCount)
{
    for (int i = 0; i < playerCount; i++)
    {
        printf("\033[31m=========== %s ===========\n\033[0m", players[i].name);
        int numberOfCards = players[i].sizeHand;
        int rows = (numberOfCards + MAX_COLUMNS - 1) / MAX_COLUMNS; // Calcul du nombre de lignes

        // Affichage des cartes ligne par ligne
        for (int cardRow = 0; cardRow < rows; cardRow++)
        {
            // Affichage des cartes (lignes de chaque carte)
            for (int h = 0; h < 3; h++)
            { // height of each card
                for (int col = 0; col < MAX_COLUMNS; col++)
                {
                    int index = cardRow * MAX_COLUMNS + col;
                    if (index < numberOfCards)
                    {
                        displayCardLine(players[i].hand[index], h); // Affiche la ligne de la carte
                        printf(" ");
                    }
                    else
                    {
                        printf("       "); // Espace vide pour les cartes manquantes
                    }
                }
                printf("\n");
            }

            // Affichage des indices sous les cartes
            for (int col = 0; col < MAX_COLUMNS; col++)
            {
                int index = cardRow * MAX_COLUMNS + col;
                if (index < numberOfCards)
                {
                    printf("  %2d   ", index + 1); // Affiche l'indice aligné sous la carte
                }
                else
                {
                    printf("       "); // Espace vide pour les cartes manquantes
                }
            }
            printf("\n\n"); // Espacement entre les lignes de cartes
        }
    }
}

void displayCardWithName(Card *card, const char *name)
{
    if (card == NULL || name == NULL)
    {
        printf("Invalid card or name.\n");
        return;
    }

    printf("Card Name: %s\n", name);
    printf("╔═══╗\n");
    if (card->state == 1) // Carte visible
        printf("║%3d║\n", card->value);
    else // Carte cachée
        printf("║ ??║\n");
    printf("╚═══╝\n");
}