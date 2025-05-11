#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "display.h"

#define MAX_HAND_SIZE 15
#define MIN_HAND_SIZE 5

// Frees the memory allocated for a player and its associated resources
void destructPlayer(Player *player)
{
    if (player != NULL)
    {
        printf("Destructing player %s\n", player->name);
        displayLoading();
        if (player->hand != NULL)
        {
            free(player->hand);
            player->hand = NULL; // Avoid double free
        }
        if (player->name != NULL)
        {
            free(player->name);
            player->name = NULL; // Avoid double free
        }
        free(player);
    }
}

// Allocates memory for a new player and returns a pointer to it
Player *constructPlayer()
{
    Player *player = malloc(sizeof(Player));
    if (player == NULL)
    {
        perror("Memory allocation failed");
        void destructPlayer(Player * player);
        exit(EXIT_FAILURE);
    }
    return player;
}

// Initializes a player with the given attributes
void initPlayer(Player *p, int score, char *name, int ai, int sizeHand)
{
    p->score = score;
    p->ai = ai;
    p->name = name;
    p->sizeHand = sizeHand;
}

// Prompts the user to choose a name and returns it as a dynamically allocated string
char *choiceName()
{
    int size = 0;
    char *name = NULL;

    do
    {
        if (size != 0)
        {
            printf("Enter a valid value\n");
        }
        printf("How many letters will your username contain (max 25):\n");
        scanf("%d", &size);
        checkScanf(); // Clear the input buffer
    } while (size < 1 || size > 25);

    name = malloc(sizeof(char) * (size + 1));
    if (name == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    name[0] = '\0';

    do
    {
        printf("Enter your username:\n");
        scanf("%s", name);
        checkScanf(); // Clear the input buffer
    } while (strlen(name) == 0);
    name[size] = '\0';

    return name;
}

// Randomly selects the size of a player's hand within the defined range
int selectSizeHand()
{
    return rand() % (MAX_HAND_SIZE - MIN_HAND_SIZE + 1) + MIN_HAND_SIZE;
}

// Handles the logic for a player's turn, including drawing or discarding cards
void playerTurn(Player *p, Discard *d, Stack *s)
{
    Card *card = getLastCardFromDiscard(d);
    int choice = 0;
    if (card == NULL)
    {
        perror("No card to discard.\n");
        exit(EXIT_FAILURE);
    }
    printf("\nIt's %s's turn", p->name);
    displayLoading();
    displayPlayerCards(p);
    displayCardWithName(card, "Card to discard");
    do
    {
        if (choice > 0)
        {
            printf("Invalid choice. Please enter 1 or 2.\n");
        }
        printf("If you want to draw a card, enter 1. Otherwise, if you want to take the card from the discard pile, enter 2:\n");
        scanf("%d", &choice);
        checkScanf(); // Clear the input buffer
    } while (choice != 1 && choice != 2);

    if (choice == 1)
    {
        card = getCardFromStack(s);
        if (card == NULL)
        {
            perror("No card to draw.\n");
            exit(EXIT_FAILURE);
        }

        printf("%s draws a card: %d", p->name, card->value);
        displayLoading();
        displayCardWithName(card, "Card to stack");
        choice = -1;
        do
        {
            if (choice > -1)
            {
                printf("Invalid choice. Please enter a valid number.\n");
            }
            printf("Enter 0 to put the card in the discard pile or choose the number with which you want to exchange it (0-%d):\n", p->sizeHand);
            scanf("%d", &choice);
            checkScanf(); // Clear the input buffer
        } while (choice < 0 || choice > p->sizeHand);

        if (choice == 0)
        {
            addCardToDiscard(d, card);
            printf("%s puts the card in the discard pile", p->name);
            displayLoading();
            displayCardWithName(card, "Card to discard");

            choice = 0;
            do
            {
                if (choice > 0)
                {
                    printf("Invalid choice. Please enter a valid number.\n");
                }
                printf("Which card do you want to flip (1-%d):\n", p->sizeHand);
                scanf("%d", &choice);
                checkScanf(); // Clear the input buffer
            } while (choice < 1 || choice > p->sizeHand);
            p->hand[choice - 1]->state = 1; // Flip the selected card
        }
        else
        {
            Card *temp = p->hand[choice - 1];
            p->hand[choice - 1] = card; // Replace the selected card with the drawn card
            addCardToDiscard(d, temp);  // Add the replaced card to the discard pile
        }
        displayLoading();
    }
    else
    {
        displayPlayerCards(p);
        printf("%s takes the card from the discard pile: %d", p->name, card->value);
        displayLoading();
        removeLastCardFromDiscard(d); // Remove the card from the discard pile
        choice = 0;
        do
        {
            if (choice > 0)
            {
                printf("Invalid choice. Please enter a valid number.\n");
            }
            printf("Choose the number with which you want to exchange (1-%d):\n", p->sizeHand);
            scanf("%d", &choice);
            checkScanf(); // Clear the input buffer
        } while (choice < 0 || choice > p->sizeHand);
        Card *temp = p->hand[choice - 1];
        p->hand[choice - 1] = card; // Replace the selected card with the discard card
        addCardToDiscard(d, temp);  // Add the replaced card to the discard pile
        displayPlayerCards(p);
        displayCardWithName(card, "Card to discard");
        printf("\n");
        displayLoading();
    }
}