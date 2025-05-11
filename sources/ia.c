#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ia.h"
#include "display.h"
#include "card.h"

// Finds the index of the card with the highest value in the AI's hand
int getIndexHighestCard(Player *p)
{
    if (p->sizeHand > 0)
    {
        int index = 0;
        for (int i = 1; i < p->sizeHand; i++)
        {
            // Check if the card is face up and has a higher value
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

// Flips the first face-down card in the AI's hand
void turnStateCard(Player *p)
{
    for (int i = 0; i < p->sizeHand; i++)
    {
        if (p->hand[i]->state == 0) // Check if the card is face down
        {
            p->hand[i]->state = 1; // Flip the card
            displayPlayerCards(p);
            printf("AI %s flips card #%d.\n", p->name, i);
            displayLoading();
            i = p->sizeHand + 1; // Exit the loop after flipping one card
        }
    }
}

// Handles the AI's turn, including drawing, discarding, and swapping cards
void iaTurn(Player *p, Stack *s, Discard *d)
{
    printf("\n AI %s is playing its turn", p->name);
    displayLoading();
    printf("\n");

    // Get the index of the card with the highest value
    int indexMax = getIndexHighestCard(p);
    if (indexMax == -1) // Check if no valid card is found
    {
        fprintf(stderr, "AI %s cannot play because it has no valid cards.\n", p->name);
        exit(EXIT_FAILURE);
    }

    // Get the top card from the discard pile
    Card *cardToDiscard = getLastCardFromDiscard(d);
    displayPlayerCards(p);

    // Decide whether to take the discard card or draw a new card
    if (cardToDiscard != NULL && p->hand[indexMax]->value > cardToDiscard->value)
    {
        // Swap the discard card with the card in the AI's hand
        displayCardWithName(cardToDiscard, "Card to discard");
        Card *temp = p->hand[indexMax];
        p->hand[indexMax] = cardToDiscard;
        removeLastCardFromDiscard(d);
        printf("AI %s swapped the discard card %d with its card #%d", p->name, cardToDiscard->value, indexMax + 1);
        displayLoading();
        addCardToDiscard(d, temp);
    }
    else
    {
        // Draw a card from the stack
        Card *cardToStack = getCardFromStack(s);
        if (cardToStack == NULL)
        {
            fprintf(stderr, "AI %s cannot draw a card because the stack is empty.\n", p->name);
            exit(EXIT_FAILURE);
        }
        printf("AI %s draws a card", p->name);
        displayLoading();
        displayCardWithName(cardToStack, "Card to stack");

        // Decide whether to keep the drawn card or discard it
        if (cardToStack->value > p->hand[indexMax]->value)
        {
            // Discard the drawn card
            addCardToDiscard(d, cardToStack);
            printf("AI %s placed the drawn card %d in the discard pile", p->name, cardToStack->value);
            displayLoading();
            turnStateCard(p); // Flip a card in the AI's hand
        }
        else
        {
            // Swap the drawn card with the card in the AI's hand
            printf("AI %s swapped the drawn card %d with its card #%d.\n", p->name, cardToStack->value, indexMax + 1);
            Card *temp = p->hand[indexMax];
            p->hand[indexMax] = cardToStack;
            addCardToDiscard(d, temp);
        }
    }
    displayPlayerCards(p); // Display the AI's updated hand
}