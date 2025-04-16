#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "card.h"

typedef struct
{
    int score;
    char name[21];
    int ai; // 0 = player , 1 = AI player
    Card *hand;
    int sizeHand;
} Player;

void destructPlayer(Player *player)
{
    if (player != NULL)
    {
        printf("Destructing player \n");
        free(player->hand);
        free(player);
    }
}

Player *constuctPlayer(int ai, int sizeHand)
{
    Player *player = malloc(sizeof(Player));
    if (player == NULL)
    {
        perror("Memory allocation failed");
        void destructPlayer(player);
        exit(EXIT_FAILURE);
    }

    player->score = 0;
    player->name[0] = '\0';
    char name[21];
    if (ai == 0)
    {
        player->ai = 0;
        do
        {
            printf("Enter player name (max 19 characters): ");
            fgets(name, sizeof(name) - 1, stdin);
            name[strcspn(name, "\n")] = 0; // Remove newline character
            if (name[0] != '\0')
            {
                strncpy(player->name, name, sizeof(player->name) - 1);
                player->name[sizeof(player->name) - 1] = '\0'; // Ensure null termination
            }
            else
            {
                printf("Name cannot be empty. Please enter a valid name.\n");
            }
        } while (player->name[0] == '\0');
    }

    else
    {
        player->ai = 1;
        player->name[0] = 'A';
        player->name[1] = 'I';
        player->name[2] = '\0';
    }

    player->sizeHand = sizeHand;

    return player;
}

int main()
{

    return 0;
}