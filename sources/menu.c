#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"
#include "player.h"
#include "game.h"

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



void ranking(GameState*game){


    for(int i=0; i<game->playerCount -1; i++){
       for(int j=i+1; j<game->playerCount; j++){
        if(game->players[j]->score > game->players[i]->score){
            Player *temp = game->players[i];
            game->players[i] = game->players[j];
            game->players[j] = temp;
        }
        }
    }
    printf("\nClassement : \n");
    for(int i=0; i<game->playerCount; i++){
        printf("%d %d %s\n", i+1, game->players[i]->score, game->players[i]->name);
    }
}

   