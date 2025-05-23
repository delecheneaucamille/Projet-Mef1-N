#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "card.h"
#include "display.h"

#define SIZE_STACK 400
#define MIN_CARDS_VALUES -5
#define MAX_CARDS_VALUES 15

void destructStack(Stack *stack)
{
    if (stack != NULL)
    {
        printf("\033[34mDestructing card stack\033[0m");
        displayLoading();

        for (int i = 0; i < stack->sizeStack; i++)
        {
            free(stack->stack[i]);
        }
        free(stack->stack);
        free(stack);
    }
}

void shuffleStack(Stack *stack)
{
    for (int i = 0; i < stack->sizeStack; i++)
    {
        int randomIndex = rand() % stack->sizeStack;
        Card *temp = stack->stack[i];
        stack->stack[i] = stack->stack[randomIndex];
        stack->stack[randomIndex] = temp;
    }
}

void selectCardValues(int *pmin, int *pmax)
{
    int min, max;
    do
    {
        printf("\033[1;35m--- Select Card Values ---\033[0m\n");
        printf("Enter the minimum card value [%d ; %d]:\n ", MIN_CARDS_VALUES, MAX_CARDS_VALUES);
        scanf("%d", &min);
        checkScanf(); // Clear the input buffer

        printf("\n");

        printf("Enter the maximum card value [%d ; %d]:\n ", MIN_CARDS_VALUES, MAX_CARDS_VALUES);
        scanf("%d", &max);
        checkScanf(); // Clear the input buffer
        system("clear");

        if (min < MIN_CARDS_VALUES || max > MAX_CARDS_VALUES || min > max)
        {
            printf("\033[31mInvalid values. Please enter values within [%d ; %d].\033[0m\n", MIN_CARDS_VALUES, MAX_CARDS_VALUES);
        }
    } while (min < MIN_CARDS_VALUES || max > MAX_CARDS_VALUES || min > max);

    *pmin = min;
    *pmax = max;
}

Stack *initStack(int size, int min, int max)
{
    Stack *stack = malloc(sizeof(Stack));
    if (stack == NULL)
    {
        fprintf(stderr, "\033[31mMemory allocation failed for stack.\033[0m\n");
        exit(EXIT_FAILURE);
    }

    stack->sizeStack = size;
    stack->stack = malloc(sizeof(Card *) * size);
    if (stack->stack == NULL)
    {
        fprintf(stderr, "\033[31mMemory allocation failed for stack->stack.\033[0m\n");
        free(stack);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
    {
        Card *c = malloc(sizeof(Card));
        if (c == NULL)
        {
            fprintf(stderr, "\033[31mMemory allocation failed for card.\033[0m\n");
            destructStack(stack);
            exit(EXIT_FAILURE);
        }
        c->value = rand() % (max - min + 1) + min;
        c->state = 0;
        stack->stack[i] = c;
    }

    return stack;
}

Card *getCardFromStack(Stack *stack)
{
    if (stack->sizeStack > 0)
    {
        int index = stack->sizeStack - 1;
        stack->sizeStack--;
        stack->stack[index]->state = 1;
        return stack->stack[index];
    }
    printf("\033[31mError: The stack is empty.\033[0m\n");
    return NULL;
}

void printStack(Stack *stack)
{
    for (int i = 0; i < stack->sizeStack; i++)
    {
        printf("\033[34mCard %d: Value = %d, State = %d\033[0m\n", i, stack->stack[i]->value, stack->stack[i]->state);
    }
}

Discard *initDiscard()
{
    Discard *d = malloc(sizeof(Discard));
    if (d == NULL)
    {
        fprintf(stderr, "\033[31mMemory allocation failed for discard.\033[0m\n");
        exit(EXIT_FAILURE);
    }

    d->indexLastCard = 0;
    d->pile = malloc(SIZE_STACK * sizeof(Card *));
    if (d->pile == NULL)
    {
        fprintf(stderr, "\033[31mMemory allocation failed for Discard->pile.\033[0m\n");
        free(d);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < SIZE_STACK; i++)
    {
        d->pile[i] = NULL;
    }
    return d;
}

void destructDiscard(Discard *d)
{
    if (d != NULL)
    {
        for (int i = 0; i < SIZE_STACK; i++)
        {
            if (d->pile[i] != NULL)
            {
                free(d->pile[i]); // Free each card
            }
        }
        free(d->pile); // Free the array of pointers
        free(d);       // Free the Discard structure
    }
    sleep(1); // Just for fun :)
    printf("\033[34mDestructing discard\033[0m");
    displayLoading();
}

void addCardToDiscard(Discard *d, Card *c)
{
    if (d == NULL || c == NULL)
    {
        fprintf(stderr, "Error: Discard or card is NULL.\n");
        return;
    }

    c->state = 1;
    d->pile[d->indexLastCard] = c; // Add the card to the pile
    d->indexLastCard++;            // Increment the index of the last card
}

void removeLastCardFromDiscard(Discard *d)
{
    if (d == NULL || d->indexLastCard <= 0)
    {
        fprintf(stderr, "Error: Discard is empty or NULL.\n");
        return;
    }

    d->indexLastCard--;               // Decrement the index of the last card
    d->pile[d->indexLastCard] = NULL; // Remove the card from the pile
}

Card *getLastCardFromDiscard(Discard *d)
{
    if (d->indexLastCard > 0)
    {
        return d->pile[d->indexLastCard - 1];
    }
    return NULL;
}

void printDiscard(Discard *d)
{
    for (int i = 0; i < d->indexLastCard; i++)
    {
        if (d->pile[i] != NULL)
        {
            printf("\033[34mCard %d: Value = %d, State = %d\033[0m\n", i, d->pile[i]->value, d->pile[i]->state);
        }
    }
}