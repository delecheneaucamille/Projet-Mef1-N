#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "card.h"
#include "player.h"

int getIndexHighestCard(Player *p)
{
    if (p->sizeHand > 0)
    {
        int index = 0;
        for (int i = 1; i < p->sizeHand; i++)
        {
            if ((p->hand[i].value > p->hand[index].value) && (p->hand[i].state == 1))
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
        if (p->hand[i].state == 0)
        {
            p->hand[i].state = 1;
            i = p->sizeHand + 1;
            printf("IA %s retourne la carte n°%d.\n", p->name, i);
        }
    }
}

void iaTurn(Player *p, Stack *s, Discard *d)
{
    printf("IA %s joue son tour...\n", p->name);

    int indexMax = getIndexHighestCard(p);
    if (indexMax == NULL)
    {
        fprintf(stderr, "IA %s ne peut pas jouer.\n", p->name);
        exit(EXIT_FAILURE);
    }

    Card *cardToDiscard = getLastCardToDiscard(d);
    if (cardToDiscard == NULL)
    {
        fprintf(stderr, "IA %s ne peut pas jouer.\n", p->name);
        exit(EXIT_FAILURE);
    }

    if (p->hand[indexMax].value > cardToDiscard->value)
    {
        Card temp = p->hand[indexMax];
        p->hand[indexMax] = *cardToDiscard;
        removeCardFromDescard(d);
        printf("IA %s a echangé la carte de la defausse %d avec sa carte n°%d .\n", p->name, cardToDiscard->value, indexMax);
        addCardToDescard(d, cardToDiscard);
    }

    else
    {
        Card *cardToStack = getCardFromStack(s);
        if (cardToStack == NULL)
        {
            fprintf(stderr, "IA %s ne peut pas piocher.\n", p->name);
            exit(EXIT_FAILURE);
        }
        printf("IA %s pioche.\n", p->name);

        if (cardToStack->value > p->hand[indexMax].value)
        {
            addCardToDescard(d, cardToStack);
            printf("IA %s met la carte de la pioche %d dans la defausse.\n", p->name, cardToStack->value);
            turnStateCard(p);
        }
        else
        {
            printf("IA %s a echangé la carte de la pioche %d avec sa carte n°%d .\n", p->name, cardToStack->value, indexMax);
            Card temp = p->hand[indexMax];
            p->hand[indexMax] = *cardToStack;
            addCardToDescard(d, temp);
        }
    }
}
