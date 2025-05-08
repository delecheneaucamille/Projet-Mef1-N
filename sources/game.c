#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ia.h"
#include "card.h"
#include "player.h"

#define MAX_PLAYERS 4 // Max 9 players
#define MIN_SIZE_HAND 20
#define MAX_SIZE_HAND 5
#define MAX_SIZE_STACK 15
#define MIN_SIZE_STACK -5
#define SIZE_STACK 100

typedef struct
{
    Player **players;  // Liste des joueurs
    int playerCount;   // Nombre de joueurs
    int currentPlayer; // Indice du joueur courant
    Discard *discard;  // Pile de défausse
    Stack *stack;      // Tas de cartes
} GameState;

GameState *initGame(Stack *stack, Discard *discard, int currentPlayer, int playerCount)
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
    game->stack = stack;

    // Allouer de la mémoire pour les joueurs
    game->players = malloc(playerCount * sizeof(Player *));
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
    destructStack(game->stack);

    // Libérer la mémoire pour l'état du jeu
    free(game);
}

void createPlayers(GameState *game, int aiCount)
{
    for (int i = game->playerCount - 1; i > 0; i--)
    {
        game->players[i] = constuctPlayer();
        if (game->players[i] == NULL)
        {
            perror("Memory allocation failed for player");
            exit(EXIT_FAILURE);
        }
        if (aiCount > 0)
        {
            game->players[i]->name = malloc(5); // Allocate enough space for "IA" + digits
            sprintf(game->players[i]->name, "IA%d\0", i + 1 % 10);
            initPlayer(game->players[i], 0, game->players[i]->name, 1, selectSizeHand()); // IA
            aiCount--;
        }
        else
        {
            initPlayer(game->players[i], 0, choiceName(), 0, selectSizeHand()); // Human player
        }
    }
}

int selectNbPlayers()
{
    int playerCount = 0;
    do
    {
        system("clear");
        if (playerCount > 0)
        {
            printf("Invalid number of players. Please enter a value between 2 and %d.\n", MAX_PLAYERS);
        }
        printf("╔=============================================╗\n");
        printf("║    \033[32mSELECTION DU NOMBRE\033[0m       ║ \n");
        printf("║         \033[32mDE JOUEURS\033[0m           ║ \n");
        printf("╠=============================================╣\n");
        printf("║                                             ║\n");
        printf("║Veuillez entrer un nombre de joueurs (2-%d) :║\n", MAX_PLAYERS);
        printf("║                                             ║\n");
        printf("╠=============================================╣\n");

        scanf("%d", &playerCount);
    } while (playerCount < 2 || playerCount > MAX_PLAYERS);
    return playerCount;
}

int selectNbAI(GameState *game)
{
    int nbAI = 0;
    if (game->playerCount == MAX_PLAYERS)
    {
        fprintf(stderr, "Not enough players to select AI.\n");
        return 0;
    }
    do
    {
        system("clear");
        if (nbAI > 0)
        {
            printf("Invalid number of AI players. Please enter a value between 0 and %d.\n", game->playerCount - 1);
        }
        printf("╔===========================================╗\n");
        printf("║    \033[32mSELECTION DU NOMBRE\033[0m     ║\n");
        printf("║           \033[32mDE AI\033[0m            ║\n");
        printf("╠===========================================╣\n");
        printf("║                                           ║\n");
        printf("║ Enter the number of AI players (0-%d):    ║\n", game->playerCount - 1);
        printf("║                                           ║\n");
        printf("╠===========================================╣\n");
        scanf("%d", &nbAI);
    } while (nbAI < 0 || nbAI > game->playerCount - 1);

    return nbAI;
}

void turnGame(GameState *game)
{

    while (statehand(game->players[game->currentPlayer]) == 1 && game->stack->sizeStack > 0)
    {
        if (game->players[game->currentPlayer]->ai == 0)
        {
            playerTurn(game->players[game->currentPlayer], game->discard, game->stack);
        }
        else
        {
            iaTurn(game->players[game->currentPlayer], game);
        }
        game->currentPlayer = (game->currentPlayer + 1) % game->playerCount;
    }
    if (statehand(game->players[game->currentPlayer]) == 1)
    {
        printf("Le joueur %s a retourné toutes ses cartes. \n", game->players[game->currentPlayer]);
        printf("Le jeu s'arrete.\nDécompte des points...\n");
    }
    else
    {
        printf("Plus de carte dans la pioche.\n");
        printf("Le jeu s'arrete.\nDécompte des points...\n");
    }
}

void return2RandomCards(GameState *game)
{
    // Pour chaque joueur
    for (int i = 0; i < game->playerCount; i++)
    {
        int index1 = rand() % game->players[i]->sizeHand;
        int index2;
        do
        {
            index2 = rand() % game->players[i]->sizeHand;
        } while (index2 == index1);

        currentPlayer->hand[index1].state = 1;
        currentPlayer->hand[index2].state = 1;
    }
}

void distributeCards(GameState *game)
{

    for (int i = 0; i < game->playerCount; i++)
    {
        Player *currentPlayer = ;
        if (game->players[i] == NULL || game->players[i]->sizeHand == NULL)
            continue;

        Card *card = getCardFromStack(game->stack);

        for (int j = 0; j < game->players[i]->sizehand; j++)
        {
            game->players[i]->hand[j] = card;
            game->players[i]->hand[j].state = 0;
        }
    }
}

int checkEndGame(Player *player)
{
    for (int i = 0; i < player->sizeHand; i++)
    {
        if (player->hand[i].state == 0)
        {
            return 0; // Une carte n'est pas retournée
        }
    }
    return 1; // Toutes les cartes sont retournées
}

void newGame()
{

    srand(time(NULL));

    int min, max;
    selectCardValues(&min, &max);
    Stack *stack = initStack(SIZE_STACK, min, max);
    Discard *discard = initDiscard();
    GameState *game = initGame(stack, discard, 0, selectNbPlayers());
    createPlayers(game, selectNbAI(game));
    shuffleStack(stack);

    // Distribuer les cartes aux joueurs
    // Retourner 2 cartes de chaque mains

    turnGame(game);
}