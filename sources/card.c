#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "card.h"
#include "player.h"
#include "game.h"

#define SIZE_STACK 100
#define MIN_CARDS_VALUES -5
#define MAX_CARDS_VALUES 15

void destructStack(Stack *stack)
{
    if (stack != NULL)
    {
        printf("Destructing card stack...\n");
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
        printf("╔===========================================╗\n");
        printf("║   \033[32mSELECTION DES VALEURS\033[0m    ║\n");
        printf("║         \033[32mDES CARTES\033[0m         ║\n");
        printf("╠===========================================╣\n");
        printf("║                                           ║\n");
        printf("║  Veuillez entrer la valeur minimale :     ║\n");
        printf("║                                           ║\n");
        scanf("%d", &min);
        printf("╔===========================================╗\n");
        printf("║   \033[32mSELECTION DES VALEURS\033[0m    ║\n");
        printf("║         \033[32mDES CARTES\033[0m         ║\n");
        printf("╠===========================================╣\n");
        printf("║                                           ║\n");
        printf("║  Veuillez entrer la valeur maximale :     ║\n");
        printf("║                                           ║\n");
        scanf("%d", &max);

        if (min < MIN_CARDS_VALUES || max > MAX_CARDS_VALUES || min > max)
        {
            printf("Invalid values. Please enter values within [%d, %d].\n", MIN_CARDS_VALUES, MAX_CARDS_VALUES);
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
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    stack->sizeStack = size;
    stack->stack = malloc(sizeof(Card *) * size);
    if (stack->stack == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(stack);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
    {
        Card *c = malloc(sizeof(Card));
        if (c == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
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
    printf("Erreur la pioche est vide.\n");
    return NULL;
}

void printStack(Stack *stack)
{
    for (int i = 0; i < stack->sizeStack; i++)
    {
        printf("Card %d: Value = %d, State = %d\n", i, stack->stack[i]->value, stack->stack[i]->state);
    }
}

Discard *initDiscard()
{
    Discard *d = malloc(sizeof(Discard));
    d->indexLastCard = 0;

    d->pile = malloc(SIZE_STACK * sizeof(Card *));
    if (d->pile == NULL)
    {
        fprintf(stderr, "Memory allocation failed for Discard->pile\n");
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
                free(d->pile[i]); // Libérer chaque carte
            }
        }
        free(d->pile); // Libérer le tableau de pointeurs
        free(d);       // Libérer la structure Discard
    }
    sleep(1); // Just for fun :)
    printf("Destructing discard\n");
}

void addCardToDiscard(Discard *d, Card *c)
{
    if (d->indexLastCard < SIZE_STACK)
    {
        d->pile[d->indexLastCard] = c; // Ajouter la carte au tableau
        d->indexLastCard++;
    }
    else
    {
        printf("Discard is full\n");
    }
}

void removeLastCardFromDiscard(Discard *d)
{
    if (d->indexLastCard > 0)
    {
        d->indexLastCard--;
        free(d->pile[d->indexLastCard]); // Libérer la mémoire de la dernière carte
        d->pile[d->indexLastCard] = NULL;
    }
    else
    {
        printf("Discard is empty\n");
    }
}

Card *getLastCardFromDiscard(Discard *d)
{
    if (d->indexLastCard > 0)
    {
        return d->pile[d->indexLastCard - 1];
    }
    else
    {
        printf("Discard is empty\n");
        return NULL;
    }
}

void printDiscard(Discard *d)
{
    for (int i = 0; i < d->indexLastCard; i++)
    {
        if (d->pile[i] != NULL)
        {
            printf("Card %d: Value = %d, State = %d\n", i, d->pile[i]->value, d->pile[i]->state);
        }
    }
}