#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "game.h"
#include "player.h"
#include "card.h"
#include "ia.h"
#include "display.h"

#define MAX_PLAYERS 9
#define MIN_SIZE_HAND 5
#define MAX_SIZE_HAND 7
#define MIN_CARDS_VALUES -5
#define MAX_CARDS_VALUES 15
#define SIZE_STACK 100

// Initializes the game state with the given parameters
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

    // Allocate memory for an array of player pointers
    game->players = malloc(playerCount * sizeof(Player *));
    if (game->players == NULL)
    {
        perror("\033[31mMemory allocation failed for players\033[0m");
        free(game);
        exit(EXIT_FAILURE);
    }

    return game;
}

// Frees all memory associated with the game state
void destructGame(GameState *game)
{
    if (game == NULL)
    {
        return;
    }

    // Free memory for each player
    for (int i = 0; i < game->playerCount; i++)
    {
        destructPlayer(game->players[i]);
    }
    free(game->players);

    // Free memory for the discard pile and stack
    destructDiscard(game->discard);
    destructStack(game->stack);

    // Free memory for the game state
    free(game);
}

// Creates players for the game, including AI and human players
void createPlayers(GameState *game, int aiCount)
{
    int sizeHand = selectSizeHand();
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
            // Create AI player
            game->players[i]->name = malloc(5);
            if (game->players[i]->name == NULL)
            {
                perror("\033[31mMemory allocation failed for AI name\033[0m");
                exit(EXIT_FAILURE);
            }
            sprintf(game->players[i]->name, "AI%d", (i + 1) % 10);
            initPlayer(game->players[i], 0, game->players[i]->name, 1, sizeHand);
            aiCount--;
        }
        else
        {
            // Create human player
            initPlayer(game->players[i], 0, choiceName(), 0, sizeHand);
        }
    }
}

// Prompts the user to select the number of players
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
        printf("\033[1;35m---  Number Of Players ---\033[0m\n");
        printf(" Please enter the number of players (2-%d):  \n", MAX_PLAYERS);

        scanf("%d", &playerCount);
    } while (playerCount < 2 || playerCount > MAX_PLAYERS);
    return playerCount;
}

// Prompts the user to select the number of AI players
int selectNbAI(GameState *game)
{
    int nbAI = -1;
    do
    {
        system("clear");
        if (nbAI > -1)
        {
            printf("\033[31mInvalid number of AI players. Please enter a value between 0 and %d.\033[0m\n", game->playerCount - 1);
        }
        printf("\033[1;35m---  Number Of AI  ---\033[0m\n");
        printf(" Enter the number of AI players (0-%d):\n", game->playerCount);
        scanf("%d", &nbAI);
    } while (nbAI < -1 || nbAI > game->playerCount);

    return nbAI;
}

// Checks if the game has ended for a specific player
int checkEndGame(Player *player)
{
    for (int i = 0; i < player->sizeHand; i++)
    {
        if (player->hand[i]->state == 0) // Check if any card is face down
        {
            return 0; // Game is not over
        }
    }
    return 1; // All cards are flipped
}

// Handles the main game loop, alternating turns between players
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

// Flips two random cards for each player at the start of the game
void return2RandomCards(GameState *game)
{
    for (int i = 0; i < game->playerCount; i++)
    {
        int index1 = rand() % game->players[i]->sizeHand;
        int index2;
        do
        {
            index2 = rand() % game->players[i]->sizeHand;
        } while (index2 == index1);

        game->players[i]->hand[index1]->state = 1;
        game->players[i]->hand[index2]->state = 1;
    }
}

// Distributes cards to all players from the stack
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
            currentPlayer->hand = malloc(currentPlayer->sizeHand * sizeof(Card *));
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

            currentPlayer->hand[j] = card;
            currentPlayer->hand[j]->state = 0;
        }
    }
}

// Calculates the ranking of players based on their scores
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
            score += game->players[i]->hand[j]->value;
        }
        game->players[i]->score = score;
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

// Starts a new game, initializing all components and running the game loop
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

    createPlayers(game, selectNbAI(game));
    printf("\033[34mThe players are created\033[0m");
    displayLoading();

    shuffleStack(stack);
    printf("\033[34mThe stack is shuffled\033[0m");
    displayLoading();

    distributeCards(game);
    printf("\033[34mThe cards have been distributed\033[0m");
    displayLoading();

    addCardToDiscard(discard, getCardFromStack(stack));
    printf("\033[34mThe first card from the stack goes to the discard pile\033[0m");
    displayLoading();

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
    displayLoading();
    printf("\033[34mThe game begins!\033[0m\n");
    displayLoading();

    system("clear");

    turnGame(game);

    Player **ranking = calculateRanking(game);
    printf("\033[34mFinal ranking:\033[0m\n");
    for (int i = 0; i < game->playerCount; i++)
    {
        printf("%s : %d points\n", ranking[i]->name, ranking[i]->score);
    }

    sleep(TIME_SLEEP * 5);

    free(ranking);
    destructGame(game);
}