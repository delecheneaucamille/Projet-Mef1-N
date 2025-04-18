#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE_STACK 100
#define MIN_SIZE_STACK -5
#define MAX_SIZE_STACK 15

typedef struct
{
    int value;
    int state;
} Card;

void destructStack(Card **stackCard, int size)
{
    if (stackCard != NULL)
    {
        printf("Destructing card... \n");
        for (int i = 0; i < size; i++)
        {
            free(stackCard[i]);
        }
    }
    sleep(1); // Just for fun :)
    printf("Destructing card stack \n");
    free(stackCard);
}

void shuffleStack(Card **stackCard, int size)
{
    for (int i = 0; i < size; i++)
    {
        int randomIndex = rand() % size;
        Card *temp = stackCard[i];
        stackCard[i] = stackCard[randomIndex];
        stackCard[randomIndex] = temp;
    }
}

void selectCardValues(int *pmin, int *pmax)
{
    int min, max;
    do
    {
        printf("Enter the minimum value of the card : \n");
        scanf("%d", &min);
        printf("Enter the maximum value of the card : \n");
        scanf("%d", &max);

        if (min < MIN_SIZE_STACK || max > MAX_SIZE_STACK || min > max)
        {
            printf("Invalid values. Please enter values with [%d, %d].\n", MIN_SIZE_STACK, MAX_SIZE_STACK);
        }
    } while (min < MIN_SIZE_STACK || max > MAX_SIZE_STACK || min > max);

    *pmin = min;
    *pmax = max;
}

void initStack(Card **stackCard, int size, int min, int max)
{
    for (int i = 0; i < size; i++)
    {
        Card *c = malloc(sizeof(Card));
        if (c == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            destructStack(stackCard, size);
            exit(EXIT_FAILURE);
        }
        c->value = rand() % (max - min + 1) + min;
        c->state = 0;
        stackCard[i] = c;
    }
}

void printStack(Card **stackCard, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Card %d: Value = %d, State = %d\n", i, ((Card *)stackCard[i])->value, ((Card *)stackCard[i])->state);
    }
}

int main()
{
    srand(time(NULL));

    int min, max;
    selectCardValues(&min, &max);

    Card **stackCarte = malloc(sizeof(Card *) * SIZE_STACK);
    if (stackCarte == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        destructStack(stackCarte, SIZE_STACK);
        return 1;
    }

    initStack(stackCarte, SIZE_STACK, min, max);
    printStack(stackCarte, SIZE_STACK);
    destructStack(stackCarte, SIZE_STACK);
    return 0;
}