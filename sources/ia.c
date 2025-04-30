#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <card.h>
#include "menu.h"
#include "player.h"
#include "game.h"

void iaTurn(Player *p, GameState *game)
{
    printf("IA %s joue son tour...\n", p->name);

    int indexMax = getIndexHighestCard(p);
    if (indexMax == NULL)
    {
        perror("L'IA n'a pas de carte à jouer.\n");
        exit(EXIT_FAILURE);
    }
    if (p->hand[indexMax]->value > game->descard.value)
    {
        printf("IA %s joue la carte de valeur %d.\n", p->name, p->hand[indexMax]->value);
        game->deck[game->deck_count] = p->hand[indexMax];
        game->deck_count++;
        p->hand[indexMax] = NULL;
    }
    else
    {
        printf("IA %s ne peut pas jouer.\n", p->name);
    }
}

int getIndexHighestCard(Player *p)
{
    if (sizeHand > 0)
    {
        int index = 0;
        for (int i = 1; i < p->sizeHand; i++)
        {
            if (p->hand[i].value > p->hand[index]->value)
            {
                index = i;
            }
        }
        return index;
    }
    printf("La main de l'IA %s est vide.\n", p->name);
    return NULL;
}