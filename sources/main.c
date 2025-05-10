#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "game.h"
#include "card.h"
#include "player.h"
int main()
{
    // Initialization of the game
    printf("Welcome to the Skyjo card game!\n"); // Welcome to the Skyjo card game!
    printf("Loading resources...\n");            // Loading resources...

    // Display the main menu
    createMenu();

    // Select the game mode
    selectGameMode();

    // End of the program
    printf("Thanks for playing! See you soon.\n"); // Thanks for playing! See you soon.
}
return 0;
}