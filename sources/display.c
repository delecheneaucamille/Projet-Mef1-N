#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "player.h"
#include "game.h"
#include "colors.h"

#define MAX_COLUMNS 4
#define MAX_ROWS 3

void displayCardLine(Card c, int line) {
    switch (line) {
        case 0: 
            printf("\033[34m╔═══╗\033[0m"); // Bordure en bleu
            break;
        case 1:
            if (c.state == 1) // Carte visible
                printf("\033[35m║%3d║\033[0m", c.value); // Chiffre en magenta
            else // Carte cachée
                printf("\033[34m║ ??║\033[0m"); // Texte en bleu
            break;
        case 2:
            printf("\033[34m╚═══╝\033[0m"); // Bordure en bleu
            break;
    }
}

void displayCards(Card **cards, int numberOfPlayers, int *cardsPerPlayer) {
    for (int player = 0; player < numberOfPlayers; player++) {
        printf("\033[31m=========== Player %d ===========\n\033[0m", player + 1);
        int numberOfCards = cardsPerPlayer[player];
        int rows = (numberOfCards + MAX_COLUMNS - 1) / MAX_COLUMNS;

        for (int cardRow = 0; cardRow < rows; cardRow++) {
            for (int h = 0; h < 3; h++) { // height of each card
                for (int col = 0; col < MAX_COLUMNS; col++) {
                    int index = cardRow * MAX_COLUMNS + col;
                    if (index < numberOfCards) {
                        displayCardLine(cards[player][index], h); // Pass the card line
                        printf(" ");
                    } else {
                        printf("       ");
                    }
                }
                printf("\n");
            }
        }

        // Now display the index for each card in the last line
        int cardRow = (numberOfCards + MAX_COLUMNS - 1) / MAX_COLUMNS - 1; // Calculate the last row index
        for (int col = 0; col < MAX_COLUMNS; col++) { // Start from col = 0
            int index = cardRow * MAX_COLUMNS + col; // Calculate the correct index
            if (index < numberOfCards) {
                printf("  %2d  ", index + 1); // Add 1 to the index to start from 1
            } else {
                printf("       ");
            }
        }
        printf("\n\n");
    }
}




