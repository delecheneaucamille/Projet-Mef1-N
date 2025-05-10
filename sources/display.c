#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "display.h"
#include "colors.h"

#define MAX_COLUMNS 4
#define MAX_ROWS 3
#define TIME_SLEEP 1

void displayCardLine(Card *c, int line)
{
    switch (line)
    {
    case 0:
        printf("\033[34m╔═══╗\033[0m"); // Blue border
        break;
    case 1:
        if (c->state == 1)                                                          // Visible card
            printf("\033[34m║\033[0m\033[35m%3d\033[0m\033[34m║\033[0m", c->value); // Number in magenta
        else                                                                        // Hidden card
            printf("\033[34m║\033[0m\033[35m ??\033[0m\033[34m║\033[0m");           // Text in blue
        break;
    case 2:
        printf("\033[34m╚═══╝\033[0m"); // Blue border
        break;
    }
}

void displayPlayerCards(Player *player)
{
    if (player == NULL)
    {
        printf("Invalid player.\n");
        return;
    }

    printf("\033[31m=========== %s ===========\n\033[0m", player->name);
    int numberOfCards = player->sizeHand;
    int rows = (numberOfCards + MAX_COLUMNS - 1) / MAX_COLUMNS; // Calculate the number of rows

    // Display cards row by row
    for (int cardRow = 0; cardRow < rows; cardRow++)
    {
        // Display cards (lines of each card)
        for (int h = 0; h < 3; h++)
        { // height of each card
            for (int col = 0; col < MAX_COLUMNS; col++)
            {
                int index = cardRow * MAX_COLUMNS + col;
                if (index < numberOfCards)
                {
                    displayCardLine(player->hand[index], h); // Display the card line
                    printf(" ");
                }
                else
                {
                    printf("       "); // Empty space for missing cards
                }
            }
            printf("\n");
        }

        // Display indices below the cards
        for (int col = 0; col < MAX_COLUMNS; col++)
        {
            int index = cardRow * MAX_COLUMNS + col;
            if (index < numberOfCards)
            {
                printf("  %2d   ", index + 1); // Display the index aligned below the card
            }
            else
            {
                printf("       "); // Empty space for missing cards
            }
        }
        printf("\n\n"); // Spacing between rows of cards
    }
}

void displayCardWithName(Card *card, const char *name)
{
    if (card == NULL || name == NULL)
    {
        printf("Invalid card or name.\n");
        return;
    }

    printf("%s\n", name);
    printf("\033[34m╔═══╗\n");
    if (card->state == 1) // Visible card
        printf("║\033[35m%3d\033[0m║\n", card->value);
    else // Hidden card
        printf("║\033[35m ??\033[0m║\n");
    printf("╚═══╝\033[0m\n");
}

void displayLoading()
{
    for (int i = 0; i < 3; i++)
    {
        sleep(TIME_SLEEP); // Wait for one second
        printf(".");       // Display a dot every second
        fflush(stdout);    // Force immediate display of the dot
    }
    printf("\n\n"); // Move to the next line after the animation
}