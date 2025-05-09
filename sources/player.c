#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"

#define MIN_SIZE_HAND 5
#define MAX_SIZE_HAND 20

void destructPlayer(Player *player)
{
    if (player != NULL)
    {
        printf("Destructing player \n");
        if (player->hand != NULL)
        {
            free(player->hand);
        }
        if (player->name != NULL)
        {
            free(player->name);
        }
        free(player);
    }
}

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

void initPlayer(Player *p, int score, char *name, int ai, int sizeHand)
{
    p->score = score;
    p->ai = ai;
    p->name = name;
    p->sizeHand = sizeHand;
}

char *choiceName()
{
    int size = 0;
    char *name = NULL;

    do
    {
        if (size != 0)
        {
            printf("Enter a valid value \n");
        }
        printf("How many letters will your username contain (max 25):\n");
        scanf("%d", &size);
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
        printf("Enter your username : \n");
        scanf("%s", name);
    } while (strlen(name) == 0);
    name[size] = '\0';

    return name;
}

int selectSizeHand()
{
    return rand() % (MAX_SIZE_HAND - MIN_SIZE_HAND + 1) + MIN_SIZE_HAND;
}

void playerTurn(Player *p, Discard *d, Stack *s)
{
    Card *card = getLastCardFromDiscard(d);
    int choice = 0;
    if (card == NULL)
    {
        perror("No card to discard.\n");
        exit(EXIT_FAILURE);
    }
    displayCards(p->hand, p->sizeHand);
    displayCardWithName(card, "Card to discard");
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
        displaycardWithName(card, "Card to stack");
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
            displayCardWithName(card, "Card to discard");
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
            p->hand[choice - 1].state = 1;
        }
        else
        {
            Card *temp = &p->hand[choice];
            p->hand[choice] = *card;
            addCardToDiscard(d, temp);
        }
    }
    else
    {
        displayCards(p->hand, p->sizeHand);
        printf("%s takes the card from the discard pile: %d\n", p->name, card->value);
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
        Card *temp = &p->hand[choice - 1];
        p->hand[choice - 1] = *card;
        addCardToDiscard(d, temp);
        displayCards(p->hand, p->sizeHand);
        displayCardWithName(card, "Card to discard");
    }
}
