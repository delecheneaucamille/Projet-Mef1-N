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


void createMenu() {
    

    
    printf("╔═════════════════════════════════════╗\n");
    printf("║                                     ║\n");
    printf("║        ████  S K Y J O  ████        ║\n");
    printf("║                                     ║\n");
    printf("║        Le jeu de cartes sur le      ║\n");
    printf("║        terminal !                   ║\n");
    printf("║                                     ║\n");
    printf("╠═════════════════════════════════════╣\n");
    printf("║ 1. Nouvelle partie                  ║\n");
    printf("║ 2. Charger une partie               ║\n");
    printf("║ 3. les règles                       ║\n");
    printf("║ 4. Quitter                          ║\n");
    printf("╠═════════════════════════════════════╣\n");
    
}








int choiceGame()
{
    int choice;
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
        case 1:
            
            // initializing a new game
            break;
        case 2:
            load();
            // loading an already existing game
            break;
        case 3:
            fopen("README.md", "r");
            // redirecting to a rule page 
            break;
        case 4:
            exit(0);
            // exit the game
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
    createMenu();
    choiceGame();
    return 0;
}
