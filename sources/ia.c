#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <card.h>

#include "menu.h"
#include "player.h"
#include "game.h"

int getIndexHighestCard(Player *p)
{
    if (sizeHand > 0)
    {
        int index = 0;
        for (int i = 1; i < p->sizeHand; i++)
        {
            if ((p->hand[i].value > p->hand[index]->value) && (p->hand[i].state == 1))
            {
                index = i;
            }
        }
        return index;
    }
    printf("La main de l'IA %s est vide.\n", p->name);
    return NULL;
}

void turnStateCard(Player *p)
{
    for (int i = 0; i < p->sizeHand; i++)
    {
        if (p->hand[i]->state == 0)
        {
            p->hand[i]->state = 1;
            i = p->sizeHand + 1;
            printf("IA %s retourne la carte n°%d.\n", p->name, i);
        }
    }
}

void iaTurn(Player *p, GameState *game)
{
    printf("IA %s joue son tour...\n", p->name);

    int indexMax = getIndexHighestCard(p);
    if (indexMax == NULL)
    {
        perror("IA %s ne peut pas jouer.\n", p->name);
        exit(EXIT_FAILURE);
    }

    Card *cardToDescard = getLastCardToDescard(game->descard);
    if (cardMax == NULL)
    {
        perror("IA %s ne peut pas jouer.\n", p->name);
        exit(EXIT_FAILURE);
    }

    if (p->hand[indexMax]->value > cardToDescard->value)
    {
        Card *temp = p->hand[indexMax];
        p->hand[indexMax] = cardToDescard;
        removeCardFromDescard(game->descard);
        printf("IA %s a echangé la carte de la defausse %d avec sa carte n°%d .\n", p->name, cardToDescard->value, indexMax);
        addCardToDescard(game->descard, cardToDescard);
    }

    else
    {
        Card *cardToStack = getCardFromStack(game->stack);
        if (cardToStack == NULL)
        {
            perror("IA %s ne peut pas piocher.\n", p->name);
            exit(EXIT_FAILURE);
        }
        printf("IA %s pioche.\n", p->name);

        if (cardToStack->value > p->hand[indexMax]->value)
        {
            addCardToDescard(game->descard, cardToStack);
            printf("IA %s met la carte de la pioche %d dans la defausse.\n", p->name, cardToStack->value);
            turnStateCard(p);
        }
        else
        {
            printf("IA %s a echangé la carte de la pioche %d avec sa carte n°%d .\n", p->name, cardToStack->value, indexMax);
            Card *temp = p->hand[indexMax];
            p->hand[indexMax] = cardToStack;
            addCardToDescard(game->descard, temp);
        }
    }
}
