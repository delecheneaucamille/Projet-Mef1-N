#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "player.h"
#include "game.h"

#define MAX_COLUMNS 4
#define MAX_ROWS 3

void displayCardLine(Card c, int line) {
    switch (line) {
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

void displayCards(Card **cards, int numberOfPlayers, int *cardsPerPlayer) {
    for (int player = 0; player < numberOfPlayers; player++) {
        printf("=========== Player %d ===========\n", player + 1);
        int numberOfCards = cardsPerPlayer[player];
        int rows = (numberOfCards + MAX_COLUMNS - 1) / MAX_COLUMNS;

        for (int cardRow = 0; cardRow < rows; cardRow++) {
            for (int h = 0; h < 3; h++) { // height of each card
                for (int col = 0; col < MAX_COLUMNS; col++) {
                    int index = cardRow * MAX_COLUMNS + col;
                    if (index < numberOfCards) {
                        displayCardLine(cards[player][index], h);
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
    int numberOfPlayers = 3;
    int cardsPerPlayer[] = {12, 9, 6};

    // Dynamic allocation
    Card **cards = malloc(numberOfPlayers * sizeof(Card *));
    for (int i = 0; i < numberOfPlayers; i++) {
        cards[i] = malloc(cardsPerPlayer[i] * sizeof(Card));
        for (int j = 0; j < cardsPerPlayer[i]; j++) {
            cards[i][j].value = rand() % 13 - 2; // [-2, 10]
            cards[i][j].state = rand() % 2;     // 0 or 1
        }
    }

    displayCards(cards, numberOfPlayers, cardsPerPlayer);

    for (int i = 0; i < numberOfPlayers; i++) {
        free(cards[i]);
    }
    free(cards);

    return 0;
}
