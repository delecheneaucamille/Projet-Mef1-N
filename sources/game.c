#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ia.h"
#include "game.h"
#include "card.h"
#include "player.h"
// #include <menu.h>

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
    game->players = malloc(playerCount * sizeof(Player*));
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

void playerTurn(Player *p, Discard *d, Stack *s)
{
    Card *card = getLastCardToDiscard(d);
    int choice = 0;
    if (card == NULL)
    {
        perror("No card to discard.\n");
        exit(EXIT_FAILURE);
    }

    printf("It's %s's turn!\n", p->name);
    do
    {
        if (choice > 0)
        {
            printf("Invalid choice. Please enter 1 or 2.\n");
        }
        printf("Si vous sahouaitez piocher une carte, entrez 1, sinon, si vous souhaiter prendre la carte de la pioche entrez 2\n");
        scanf("%d", &choice);
    } while (choice != 1 && choice != 2);

    if (choice == 1)
    {
        Card *card = getCardFromStack(s);
        if (card == NULL)
        {
            perror("No card to draw.\n");
            exit(EXIT_FAILURE);
        }

        printf("%s draws a card: %d\n", p->name, card->value);
        choice = -1;
        do
        {
            if (choice > -1)
            {
                printf("Invalid choice. Please enter a valid number.\n");
            }
            printf("Entrez 0 pour mettre la carte a la defausse ou choisissez le numero avec laquelle vous vouler echanger (0-%d): \n", p->sizeHand);
            scanf("%d", &choice);
        } while (choice < 0 || choice > p->sizeHand);

        if (choice == 0)
        {
            addCardToDiscard(d, card);
            printf("%s puts the card in the discard pile.\n", p->name);

            choice = 0;
            do
            {
                if (choice > 0)
                {
                    printf("Invalid choice. Please enter a valid number.\n");
                }
                printf("Quelle carte souhaitez vous retourner (1-%d): \n", p->sizeHand);
                scanf("%d", &choice);
            } while (choice < 1 || choice > p->sizeHand);
            p->hand[choice - 1]->state = 1;
        }
        else
        {
            Card *temp = p->hand[choice];
            p->hand[choice] == card;
            addCardToDiscard(d, temp);
        }
    }
    else
    {
        printf("%s takes the card from the discard pile: %d\n", p->name, cardToDiscard->value);
        removeLastCardFromDiscard(d);
        choice = 0;
        do
        {
            if (choice > 0)
            {
                printf("Invalid choice. Please enter a valid number.\n");
            }
            printf("Choisissez le numero avec laquelle vous vouler echanger (1-%d): \n", p->sizeHand);
            scanf("%d", &choice);
        } while (choice < 0 || choice > p->sizeHand);
        Card *temp = p->hand[choice - 1];
        p->hand[choice - 1] == card;
        addCardToDiscard(d, temp);
    }
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