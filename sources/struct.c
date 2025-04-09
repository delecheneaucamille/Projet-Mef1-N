#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int value;
    int state;
} Card;

typedef struct
{
    int score;
    char name[21];
    int ai; // 0 = player , 1 = AI player
    Card *hand;
} Player;

Player *constuctPlayer()
{
    Player *player = malloc(sizeof(Player));
    if (player == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    player->score = 0;
    player->name[0] = '\0';
    char name[21];
    do
    {
        printf("Enter player name (max 19 characters): ");
        fgets(name, sizeof(name) - 1, stdin);
        name[strcspn(name, "\n")] = 0; // Remove newline character
        if (name[0] != '\0')
        {
            snprintf(player->name, sizeof(player->name), "%s", name);
        }
        else
        {
            printf("Name cannot be empty. Please enter a valid name.\n");
        }
    } while (player->name[0] == '\0');

    return player;
}

int main()
{
    Player *player = constuctPlayer();
    printf("Player name: %s\n", player->name);
    return 0;
}