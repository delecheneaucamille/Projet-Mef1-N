#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "card.h"

#define MIN_SIZE_HAND 20
#define MAX_SIZE_HAND 5

typedef struct
{
    int score;
    char *name;
    int ai; // 0 = player , 1 = AI player
    Card *hand;
    int sizeHand;
} Player;

void destructPlayer(Player *player)
{
    if (player != NULL)
    {
        printf("Destructing player \n");
        if (player->hand != NULL)
        {
            free(player->hand);
        }
        if (player->name != NULL)
        {
            free(player->name);
        }
        free(player);
    }
}

Player *constuctPlayer()
{
    Player *player = malloc(sizeof(Player));
    if (player == NULL)
    {
        perror("Memory allocation failed");
        void destructPlayer(player);
        exit(EXIT_FAILURE);
    }
    return player;
}

void initPlayer(Player *p, int score, char *name, int ai, int sizeHand)
{
    p->score;
    p->score;
    p->name = name;
    p->sizeHand = sizeHand;
}

char *choiceName()
{
    int size = 0;
    char *name = NULL;

    do
    {
        if (size > 0)
        {
            printf("Enter a valid value \n");
        }
        printf("How many letters will your username contain (max 25):\n");
        scanf("%d", &size);
    } while ((size < 26) && (size > 0));

    name = malloc(sizeof(char) * (size + 1));
    if (name == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    name[0] = "/0";

    do
    {
        printf("Enter your username : \n");
        scanf("%s", name);
    } while (name == "/0");
    name[size] = "/0";

    return name;
}

int selectSizeHand()
{
    return rand() % (MAX_SIZE_HAND - MIN_SIZE_HAND + 1) + MIN_SIZE_HAND;
}

int main()
{

    return 0;
}


void statehand(int *Player){
    
   (for(int i = 0, i < player->sizehand; i++){
       if(player->hand[i].state == 0 ){
       
        return 0;}  
       
        else{return 1;
     } 
   }
}
    
void distributeInitialCards(GameState *game) {
    // Pour chaque joueur
    for (int i = 0; i < game->playerCount; i++) {
        Player *currentPlayer = game->players[i];
        
                int index1 = rand() % game->stack->sizeStack;
                int index2;
                do {
                    index2 = rand() % game->stack->sizeStack;
                } while (index2 == index1);        
                currentPlayer->hand[0] = *game->stack->stack[index1];
                currentPlayer->hand[1] = *game->stack->stack[index2];
        
               
                currentPlayer->hand[0].state = 1;
                currentPlayer->hand[1].state = 1;
        
               
                game->stack->stack[index1] = NULL;
                game->stack->stack[index2] = NULL;
            
        }
}

void distributeInitialCards(GameState *game) {
   
    for (int i = 0; i < game->playerCount; i++) {
        Player *currentPlayer = game->players[i];

        for (int j = 0; j < 2; j++) {
            Card *card = getCardFromStack(game->stack);
            if (card == NULL) {
                fprintf(stderr, "Erreur : Stack vide pour le joueur %d\n", i);
                return;
            }

            card->state = 1;
            
            // Ajouter à la main du joueur
            currentPlayer->hand[j] = *card;
            
        
            if (j >= currentPlayer->handSize) {
                fprintf(stderr, "Erreur : Main du joueur %d trop petite\n", i);
                return;
            }
        }
    }
}