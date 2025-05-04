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
        printf("IA %s a echangé la carte de la defausse %d avec sa carte n°%d .\n", p->name, cardToDescard->value, indexMax);
        addCardToDescard(game->descard, cardToDescard);
    }
    else
    {
        printf("IA %s ne peut pas jouer.\n", p->name);
    }
}
