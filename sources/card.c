#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_STACK 100
#define MIN -5
#define MAX 15

typedef struct
{
    int value;
    int state;
} Card;

void destructStack(int *stackCard)
{
    printf("Destructing card stack \n");
    free(stackCard);
}

void shuffleStack(int *stackCard, int size)
{
    for (int i = 0; i < size; i++)
    {
        int randomIndex = rand() % size;
        int temp = stackCard[i];
        stackCard[i] = stackCard[randomIndex];
        stackCard[randomIndex] = temp;
    }
}

void selectValuesCard(int *pmin, int *pmax)
{
    int min, max;
    do
    {
        printf("Enter the minimum value of the card : \n");
        scanf("%d", &min);
        printf("Enter the maximum value of the card : \n");
        scanf("%d", &max);

        if (min < MIN || max > MAX || min > max)
        {
            printf("Invalid values. Please enter values with [%d, %d].\n", MIN, MAX);
        }
    } while (min < MIN || max > MAX || min > max);

    *pmin = min;
    *pmax = max;
}

int main()
{
    srand(time(NULL));

    int *stackCarte = malloc(sizeof(Card) * SIZE_STACK);
    if (stackCarte == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        destructStack(stackCarte);
        return 1;
    }

    shuffleStack(stackCarte, SIZE_STACK);
    destructStack(stackCarte);
    return 0;
}