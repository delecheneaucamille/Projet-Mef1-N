#include <stdio.h>
#include <stdlib.h>
#include <string.h> // #include "struct.h"
#define MIN -5
#define MAX 15

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
    do
    {
        if (choice != 0)
        {
            printf("Select valide choice\n");
        }
        printf("Press '1' play vs AI\nPress '2' play vs player\nPress '3' to load a game\nPress '4' to see the rules\nPress '5' to exit\n");
        printf("Enter your choice: \n");
        scanf("%d", &choice);
    } while ((choice < 1) || (choice > 5));
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

void selectValuesCard(int *pmin, int *pmax)
{
    int min, max;
    do
    {
        printf("Enter the minimum value of the card (%d <= min): \n", MIN);
        scanf("%d", &min);
        printf("Enter the maximum value of the card (max <= %d): \n", MAX);
        scanf("%d", &max);

        if (min < MIN || max > MAX || min > max)
        {
            printf("Invalid values. Please enter values with %d <= min <= max <= %d.\n", MIN, MAX);
        }
    } while (min < MIN || max > MAX || min > max);

    *pmin = min;
    *pmax = max;
}

int main()
{
    int min, max;
    selectValuesCard(&min, &max);
    printf("Minimum value: %d\n", min);
    printf("Maximum value: %d\n", max);
    return 0;
}