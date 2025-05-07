#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "player.h"
#include "game.h"

#define MAX_COLUMNS 4
#define MAX_ROWS 3

void displayCardLine(Card c, int line) {
    switch (line) {
        case 0: 
            printf("╔═══╗"); 
            break;
        case 1:
            if (c.state == 1)
                printf("║%3d║", c.value);
            else
                printf("║ ??║");
            break;
        case 2:
            printf("╚═══╝");
            break;
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
        for (int col = 0; col < MAX_COLUMNS; col++) {
            int index = col;
            if (index < numberOfCards) {
                printf("  %2d  ", index); // Display the index
            } else {
                printf("       ");
            }
        }
        printf("\n\n");
    }
}


void displayGameState(GameState *game) {
    printf("=========== Game State ===========\n");
    printf("Current Player: %d\n", game->currentPlayer + 1);
    printf("Number of Players: %d\n", game->playerCount);
    printf("Discard Pile:\n");
    printDiscard(game->discard);
    printf("Stack:\n");
    printStack(game->stack);
    printf("\n");
}

