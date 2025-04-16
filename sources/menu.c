#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"

typedef enum
{
    PLAY_VS_AI = 1,
    PLAY_VS_PLAYER,
    LOAD_GAME,
    SHOW_RULES,
    EXIT,
} MenuOption;

int choiceGame()
{
    int choice;
    printf("Press '1' play vs AI\nPress '2' play vs player\nPress '3' to load a game\nPress '4' to see the rules\nPress '5' to exit\n");
    printf("Enter your choice: \n");
    scanf("%d", &choice);
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
        case PLAY_VS_AI:
            printf("You chose to play against AI.\n");
            break;
        case PLAY_VS_PLAYER:
            printf("You chose to play against another player.\n");
            break;
        case LOAD_GAME:
            printf("You chose to load a game.\n");
            break;
        case SHOW_RULES:
            printf("You chose to see the rules.\n");
            break;
        case EXIT:
            printf("Exiting the game.\n");
            exit(0);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            choice = 0; // Reset choice to continue the loop
        }
    } while (choice == 0);
}

int main()
{
    int min, max;
    selectValuesCard(&min, &max);
    printf("Minimum value: %d\n", min);
    printf("Maximum value: %d\n", max);
    return 0;
}