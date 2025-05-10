#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"

void createMenu()
{
    printf("+-------------------------------------+\n");
    printf("|                                     |\n");
    printf("|         🃏 \033[1;35mC A R D  Y A R D\033[0m 🃏      |\n");
    printf("|                                     |\n");
    printf("|        Best game of the year        |\n");
    printf("|        (we swear)                   |\n");
    printf("|                                     |\n");
    printf("+-------------------------------------+\n");
    printf("| 1. New game                         |\n");
    printf("| 2. Load a previous game             |\n");
    printf("| 3. Rules                            |\n");
    printf("| 4. Exit                             |\n");
    printf("+-------------------------------------+\n");
}

int choiceGame()
{
    int choice = 0;
    do
    {
        if (choice != 0)
        {
            printf("\033[31mInvalid choice. Please try again.\033[0m\n");
        }
        printf("Enter your choice: \n");
        scanf("%d", &choice);
        system("clear");
    } while (choice < 1 || choice > 4);
    return choice;
}

void selectGameMode()
{
    int choice;
    do
    {
        choice = choiceGame();
        switch (choice)
        {
        case 1:
            newGame();
            // initializing a new game
            break;
        case 2:
            printf("Loading game...\n");
            printf("It's not implemented yet sorry :)\n");
            // loading an already existing game
            break;
        case 3:
            fopen("README.md", "r");
            // redirecting to a rule page
            break;
        case 4:
            exit(-1);
            // exit the game
            break;

        default:
            printf("\031[32mInvalid choice. Please try again.\033[0m\n");
            choice = 0; // Reset choice to continue the loop
        }
    } while (choice == 0);
}

void ranking(GameState *game)
{
    for (int i = 0; i < game->playerCount; i++)
    {
        game->players[i]->score = 0;

        for (int j = 0; j < game->players[i]->sizeHand; j++)
        {
            if (game->players[i]->hand[j]->state == 1)
            {
                game->players[i]->score += game->players[i]->hand[j]->value;
            }
        }
        for (int i = 0; i < game->playerCount; i++)
        {
            for (int j = 0; j < game->playerCount; j++)
            {
                if (game->players[i]->score < game->players[j]->score)
                {
                    Player *temp = game->players[i];
                    game->players[i] = game->players[j];
                    game->players[j] = temp;
                }
            }
        }
    }
    printf("\nRanking:\n");
    for (int i = 0; i < game->playerCount; i++)
    {
        printf("Player %s; Score %d\n", game->players[i]->name, game->players[i]->score);
    }
}