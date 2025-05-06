#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ia.h"
#include "game.h"
#include "card.h"
#include "player.h"
// #include <menu.h>

#define SIZE_STACK 100
#define MIN_SIZE_STACK -5
#define MAX_SIZE_STACK 15
#define MAX_PLAYERS 4

typedef struct
{
    Player **players;  // Liste des joueurs
    int playerCount;   // Nombre de joueurs
    int currentPlayer; // Indice du joueur courant
    Discard *discard;  // Pile de défausse
    Stack *deck;       // Tas de cartes
} GameState;

GameState *initGame(int playerCount, Discard *discard, int currentPlayer, Stack *deck)
{
    if (playerCount < 1 || playerCount > MAX_PLAYERS)
    {
        fprintf(stderr, "Invalid number of players: %d\n", playerCount);
        exit(EXIT_FAILURE);
    }

    GameState *game = malloc(sizeof(GameState));
    if (game == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    game->playerCount = playerCount;
    game->currentPlayer = currentPlayer;
    game->discard = discard;
    game->deck = deck;

    // Allouer de la mémoire pour les joueurs
    game->players = malloc(playerCount * sizeof(*Player));
    if (game->players == NULL)
    {
        perror("Memory allocation failed for players");
        free(game);
        exit(EXIT_FAILURE);
    }

    return game;
}

void destructGame(GameState *game)
{
    if (game == NULL)
    {
        return;
    }

    // Libérer la mémoire pour chaque joueur
    for (int i = 0; i < game->playerCount; i++)
    {
        destructPlayer(game->players[i]);
    }
    free(game->players);

    // Libérer la mémoire pour la pile de défausse
    destructDescard(game->discard);

    // Libérer la mémoire pour le tas de cartes
    destructStack(game->deck);

    // Libérer la mémoire pour l'état du jeu
    free(game);
}

/*
    *
    *
    * C'est pas bon donc je vais le refaire
    *
    *


void createPlayers(GameState *game, int iaCount)
{
    for (int i = 0; i < game->playerCount; i++)
    {
        game->players[i] = constuctPlayer();
        if (game->players[i] == NULL)
        {
            perror("Memory allocation failed for player");
            exit(EXIT_FAILURE);
        }
        char *name = choiceName();
        int ai = 0;
        if (iaCount > 0 && i >= (game->playerCount - iaCount))
        {
            ai = 1;
        }
        initPlayer(game->players[i], 0, name, ai, selectSizeHand());
    }
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

void choiceNumberOfPlayers(int *playerCount, int *iaCount)
{
    *playerCount = 1;
    do
    {
        if (*playerCount < 1 || *playerCount > MAX_PLAYERS)
            ;
        {
            fprintf(stderr, "Invalid number of players: %d\n", *playerCount);
        }
        printf("Enter the number of players (1-%d): ", MAX_PLAYERS);
        scanf("%d", *playerCount);
    } while (*playerCount < 1 || *playerCount > MAX_PLAYERS);

    if (*playerCount == MAX_PLAYERS)
    {
        *iaCount = 0;
    }
    else
    {
        *iaCount = 1;
        do
        {
            if (*iaCount < max(2 - *playerCount, 0) || *iaCount > (MAX_PLAYERS - *playerCount))
                ;
            {
                fprintf("Invalid number of AIs: %d\n", *iaCount);
            }
            printf("Enter the number of AIs playing with you (%d-%d): ", max(2 - *playerCount, 0), (MAX_PLAYERS - *playerCount));
            scanf("%d", playerCount);
        } while (*iaCount < max(2 - *playerCount, 0) || *iaCount > (MAX_PLAYERS - *playerCount));
    }
}
*/