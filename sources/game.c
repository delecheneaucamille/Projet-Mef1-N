#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "ia.h"
#include "card.h"
#include "player.h"
#include "display.h"

#define MAX_PLAYERS 4 // Max 9 players
#define MIN_SIZE_HAND 5
#define MAX_SIZE_HAND 20
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
        fprintf(stderr, "\033[31mInvalid number of players: %d\033[0m\n", playerCount);
        exit(EXIT_FAILURE);
    }

    GameState *game = malloc(sizeof(GameState));
    if (game == NULL)
    {
        perror("\033[31mMemory allocation failed\033[0m");
        exit(EXIT_FAILURE);
    }

    game->playerCount = playerCount;
    game->currentPlayer = currentPlayer;
    game->discard = discard;
    game->stack = stack;

    // Allouer de la mémoire pour un tableau de pointeurs vers les joueurs
    game->players = malloc(playerCount * sizeof(Player *));
    if (game->players == NULL)
    {
        perror("\033[31mMemory allocation failed for players\033[0m");
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
    destructDiscard(game->discard);

    // Libérer la mémoire pour le tas de cartes
    destructStack(game->stack);

    // Libérer la mémoire pour l'état du jeu
    free(game);
}

void createPlayers(GameState *game, int aiCount)
{
    for (int i = 0; i < game->playerCount; i++)
    {
        game->players[i] = constructPlayer();
        if (game->players[i] == NULL)
        {
            perror("\033[31mMemory allocation failed for player\033[0m");
            exit(EXIT_FAILURE);
        }
        if (aiCount > 0)
        {
            game->players[i]->name = malloc(5); // Allocate enough space for "AI" + digits
            if (game->players[i]->name == NULL)
            {
                perror("\033[31mMemory allocation failed for AI name\033[0m");
                exit(EXIT_FAILURE);
            }
            sprintf(game->players[i]->name, "AI%d", (i + 1) % 10);
            initPlayer(game->players[i], 0, game->players[i]->name, 1, selectSizeHand()); // AI
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
            printf("\033[31mInvalid number of players. Please enter a value between 2 and %d.\033[0m\n", MAX_PLAYERS);
        }
        printf("\033[34m╔=============================================╗\n");
        printf("║    SELECT NUMBER                            ║\n");
        printf("║         OF PLAYERS                          ║\n");
        printf("╠=============================================╣\n");
        printf("║                                             ║\n");
        printf("║ Please enter the number of players (2-%d):  ║\n", MAX_PLAYERS);
        printf("║                                             ║\n");
        printf("╠=============================================╣\033[0m\n");

        scanf("%d", &playerCount);
    } while (playerCount < 2 || playerCount > MAX_PLAYERS);
    return playerCount;
}

int selectNbAI(GameState *game)
{
    int nbAI = 0;
    if (game->playerCount == MAX_PLAYERS)
    {
        fprintf(stderr, "\033[31mNot enough players to select AI.\033[0m\n");
        return 0;
    }
    do
    {
        system("clear");
        if (nbAI > 0)
        {
            printf("\033[31mInvalid number of AI players. Please enter a value between 0 and %d.\033[0m\n", game->playerCount - 1);
        }
        printf("\033[34m╔===========================================╗\n");
        printf("║    SELECT NUMBER                          ║\n");
        printf("║           OF AI                           ║\n");
        printf("╠===========================================╣\n");
        printf("║                                           ║\n");
        printf("║ Enter the number of AI players (0-%d):     ║\n", game->playerCount - 1);
        printf("║                                           ║\n");
        printf("╠===========================================╣\033[0m\n");
        scanf("%d", &nbAI);
    } while (nbAI < 0 || nbAI > game->playerCount - 1);

    return nbAI;
}

int checkEndGame(Player *player)
{
    for (int i = 0; i < player->sizeHand; i++)
    {
        if (player->hand[i].state == 0)
        {
            return 0; // A card is still face down
        }
    }
    return 1; // All cards are flipped
}

void displayLoading()
{
    for (int i = 0; i < 3; i++)
    {
        sleep(1); // Attend une seconde
        printf("."); // Affiche un point à chaque seconde
        fflush(stdout); // Force l'affichage immédiat du point
    }
    printf("\n\n"); // Passe à la ligne après l'animation
}

void turnGame(GameState *game)
{
    while (checkEndGame(game->players[game->currentPlayer]) == 0 && game->stack->sizeStack > 0)
    {
        if (game->players[game->currentPlayer]->ai == 0)
        {
            playerTurn(game->players[game->currentPlayer], game->discard, game->stack);
        }
        else
        {
            iaTurn(game->players[game->currentPlayer], game->stack, game->discard);
        }
        game->currentPlayer = (game->currentPlayer + 1) % game->playerCount;
    }
    if (checkEndGame(game->players[game->currentPlayer]) == 1)
    {
        printf("\033[34mPlayer %s has flipped all their cards.\033[0m\n", game->players[game->currentPlayer]->name);
        printf("\033[34mThe game ends.\nCalculating scores\033[0m");
        displayLoading();
    }
    else
    {
        printf("\033[34mNo more cards in the stack.\033[0m\n");
        printf("\033[34mThe game ends.\nCalculating scores\033[0m");
        displayLoading();
    }
}

void return2RandomCards(GameState *game)
{
    // For each player
    for (int i = 0; i < game->playerCount; i++)
    {
        int index1 = rand() % game->players[i]->sizeHand;
        int index2;
        do
        {
            index2 = rand() % game->players[i]->sizeHand;
        } while (index2 == index1);

        game->players[i]->hand[index1].state = 1;
        game->players[i]->hand[index2].state = 1;
    }
}

void distributeCards(GameState *game)
{
    for (int i = 0; i < game->playerCount; i++)
    {
        Player *currentPlayer = game->players[i];
        if (currentPlayer == NULL)
        {
            fprintf(stderr, "Error: Player %d is NULL.\n", i);
            continue;
        }
        if (currentPlayer->sizeHand <= 0)
        {
            fprintf(stderr, "Error: Player %d has an invalid hand size.\n", i);
            continue;
        }

        if (currentPlayer->hand == NULL)
        {
            currentPlayer->hand = malloc(currentPlayer->sizeHand * sizeof(Card));
            if (currentPlayer->hand == NULL)
            {
                perror("Memory allocation failed for player's hand");
                exit(EXIT_FAILURE);
            }
        }

        for (int j = 0; j < currentPlayer->sizeHand; j++)
        {
            if (game->stack->sizeStack <= 0)
            {
                fprintf(stderr, "Error: Not enough cards in the stack to distribute.\n");
                exit(EXIT_FAILURE);
            }

            Card *card = getCardFromStack(game->stack);
            if (card == NULL)
            {
                fprintf(stderr, "Error: Failed to retrieve a card from the stack.\n");
                exit(EXIT_FAILURE);
            }

            currentPlayer->hand[j] = *card;
            currentPlayer->hand[j].state = 0;
        }
    }
}

Player **calculateRanking(GameState *game)
{
    Player **ranking = malloc(game->playerCount * sizeof(Player *));
    if (ranking == NULL)
    {
        perror("Memory allocation failed for ranking");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < game->playerCount; i++)
    {
        int score = 0;
        for (int j = 0; j < game->players[i]->sizeHand; j++)
        {
            score += game->players[i]->hand[j].value;
        }
        game->players[i]->score = score;
    }

    for (int i = 0; i < game->playerCount; i++)
    {
        ranking[i] = game->players[i];
    }

    for (int i = 0; i < game->playerCount - 1; i++)
    {
        for (int j = i + 1; j < game->playerCount; j++)
        {
            if (ranking[i]->score > ranking[j]->score)
            {
                Player *temp = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = temp;
            }
        }
    }

    return ranking;
}

void newGame()
{
    srand(time(NULL));

    int min, max;
    selectCardValues(&min, &max);
    Stack *stack = initStack(SIZE_STACK, min, max);
    if (stack == NULL)
    {
        fprintf(stderr, "\033[31mError: Failed to initialize stack.\033[0m\n");
        exit(EXIT_FAILURE);
    }

    Discard *discard = initDiscard();
    if (discard == NULL)
    {
        fprintf(stderr, "\033[31mError: Failed to initialize discard.\033[0m\n");
        destructStack(stack);
        exit(EXIT_FAILURE);
    }

    GameState *game = initGame(stack, discard, 0, selectNbPlayers());
    if (game == NULL)
    {
        fprintf(stderr, "\033[31mError: Failed to initialize game state.\033[0m\n");
        destructStack(stack);
        destructDiscard(discard);
        exit(EXIT_FAILURE);
    }

    system("clear");
    printf("\033[34mThe game is initialized\033[0m");
    displayLoading();
    

    createPlayers(game, selectNbAI(game));
    printf("\033[34mThe players are created\033[0m");
    displayLoading();
    

    shuffleStack(stack);
    printf("\033[34mThe stack is shuffled\033[0m");
    displayLoading();
    

    distributeCards(game);
    printf("\033[34mThe cards have been distributed\033[0m\n");
    sleep(1);

    // Vérifiez les joueurs et leurs mains avant d'afficher
    for (int i = 0; i < game->playerCount; i++)
    {
        if (game->players[i] == NULL)
        {
            fprintf(stderr, "\033[31mError: Player %d is NULL.\033[0m\n", i);
            exit(EXIT_FAILURE);
        }
        if (game->players[i]->hand == NULL)
        {
            fprintf(stderr, "\033[31mError: Player %s has no hand allocated.\033[0m\n", game->players[i]->name);
            exit(EXIT_FAILURE);
        }
    }

    return2RandomCards(game);
    printf("\033[34mThe cards are shuffled and distributed!!!\033[0m\n\n");
    sleep(1);
    printf("\033[34mThe game begins!\033[0m\n");

    turnGame(game);

    Player **ranking = calculateRanking(game);
    printf("\033[34mFinal ranking:\033[0m\n");
    for (int i = 0; i < game->playerCount; i++)
    {
        printf("%s : %d points\n", ranking[i]->name, ranking[i]->score);
    }

    // Libérer la mémoire
    free(ranking);
    destructGame(game);
}