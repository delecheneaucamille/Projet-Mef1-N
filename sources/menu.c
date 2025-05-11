#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "display.h"

// Function to display the main menu
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

// Function to get the user's choice from the menu
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
    } while (choice < 1 || choice > 4); // Ensure the choice is valid
    return choice;
}

// Function to handle the selected game mode
int selectGameMode()
{
    int choice;
    do
    {
        choice = choiceGame();
        switch (choice)
        {
        case 1:
            system("clear");
            newGame(); // Start a new game
            return 1;
        case 2:
            printf("Loading game...\n");
            printf("It's not implemented yet sorry :)\n");
            displayLoading();
            return 1;
        case 3:
            printf("\n\033[1;34mDisplaying the rules:\033[0m\n\n");
            displayLoading();
#ifdef _WIN32
            system("type README.md"); // Windows command to display file content
#else
            system("cat README.md"); // Linux/macOS command to display file content
#endif
            printf("\nPress Enter to return to the menu...\n");
            getchar(); // Wait for user input
            getchar(); // To handle the newline left by scanf
            return 1;
        case 4:
            exit(0); // Exit the game
            return 0;
        default:
            printf("\033[31mInvalid choice. Please try again.\033[0m\n");
            choice = 0; // Reset choice to continue the loop
        }
    } while (choice == 0);
    return 0;
}
