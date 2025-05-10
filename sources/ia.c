#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ia.h"
#include "display.h" // For displayPlayerCards and displayCardWithName
#include "card.h"    // For getLastCardFromDiscard

int getIndexHighestCard(Player *p)
{
    if (p->sizeHand > 0)
    {
        int index = 0;
        for (int i = 1; i < p->sizeHand; i++)
        {
            if ((p->hand[i]->value > p->hand[index]->value) && (p->hand[i]->state == 1))
            {
                index = i;
            }
        }
        return index; // Returns the index of the card with the highest value
    }
    printf("The hand of AI %s is empty.\n", p->name);
    return -1; // Returns -1 to indicate that there is no valid card
}

void turnStateCard(Player *p)
{
    for (int i = 0; i < p->sizeHand; i++)
    {
        if (p->hand[i]->state == 0)
        {
            p->hand[i]->state = 1;
            displayPlayerCards(p);
            printf("AI %s flips card #%d.\n", p->name, i);
            i = p->sizeHand + 1;
        }
    }
}

void iaTurn(Player *p, Stack *s, Discard *d)
{
    printf("AI %s is playing its turn...\n\n", p->name);

    int indexMax = getIndexHighestCard(p);
    if (indexMax == -1) // Checks if no valid card is found
    {
        fprintf(stderr, "AI %s cannot play because it has no valid cards.\n", p->name);
        exit(EXIT_FAILURE);
    }

    Card *cardToDiscard = getLastCardFromDiscard(d);
    displayPlayerCards(p);
    if (cardToDiscard != NULL)
    {
        displayCardWithName(cardToDiscard, "Card to discard");
    }

    if (cardToDiscard != NULL && p->hand[indexMax]->value > cardToDiscard->value)
    {
        Card *temp = p->hand[indexMax];
        p->hand[indexMax] = cardToDiscard;
        removeLastCardFromDiscard(d);
        printf("AI %s swapped the discard card %d with its card #%d.\n", p->name, cardToDiscard->value, indexMax + 1);
        addCardToDiscard(d, temp);
    }
    else
    {
        Card *cardToStack = getCardFromStack(s);
        if (cardToStack == NULL)
        {
            fprintf(stderr, "AI %s cannot draw a card because the stack is empty.\n", p->name);
            exit(EXIT_FAILURE);
        }
        displayCardWithName(cardToStack, "Card to stack");
        printf("AI %s draws a card.\n", p->name);

        if (cardToStack->value > p->hand[indexMax]->value)
        {
            addCardToDiscard(d, cardToStack);
            printf("AI %s placed the drawn card %d in the discard pile.\n", p->name, cardToStack->value);
            turnStateCard(p);
        }
        else
        {
            printf("AI %s swapped the drawn card %d with its card #%d.\n", p->name, cardToStack->value, indexMax + 1);
            Card *temp = p->hand[indexMax];
            p->hand[indexMax] = cardToStack;
            addCardToDiscard(d, temp);
        }
    }
    displayPlayerCards(p);
}