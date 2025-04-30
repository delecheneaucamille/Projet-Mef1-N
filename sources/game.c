#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <card.h>
#include <player.h>
#include <menu.c>

 

#define DECK_SIZE 52
#define HAND_SIZE 5
#define MAX_HAND_SIZE 10
#define MIN_HAND_SIZE 2
#define MAX_PLAYERS 4
#define MIN_PLAYERS 2



    typedef struct
    {
        int value;
        int state;
    } Card;
    
    typedef struct {
        Player players; 
        int currentPlayer;   // Indice du joueur courant
        Discard discrad;
        int number_players;
    } GameState;




    Card *getLastCardToDescard(Descard *d, int index);



void init_game(GameState* game, int number_players, int min_val, int max_val) {
    if(""number_players < MIN_PLAYERS || number_players > MAX_PLAYERS) {
        printf("invalid number of players. Should be between %d and %d.\n", MIN_PLAYERS, MAX_PLAYERS);
        return;
    }
    
    game->number_players = number_players;
    game->currentPlayer = 0;

   

    // Initialisation simple du deck
    for(int i = 0; i < hand; i++) {
        game->hand[i].value = (rand() % (max_val - min_val + 1)) +min_val;
        game->hand[i].state = 0;
    }

    // Distribution des cartes
    for(int p = 0; p < players; p++) {
        for(int c = 0; c < HAND_SIZE; c++) {
            game->hands[p][c] = game->deck[--game->deck_count];
            game->hands[p][c].is_visible = 0; // Cartes cachées au départ
        }
        game->discard_counts[p] = 0;
    }
}

void player_turn(GameState* game) {
    int p = game->current_player;
    printf("\n--- Joueur %d ---\n", p+1);
    
    // Afficher main
    printf("Vos cartes:\n");
    for(int i = 0; i < HAND_SIZE; i++) {
        if(game->hands[p][i].is_visible)
            printf("%d: [%d] ", i, game->hands[p][i].value);
        else
            printf("%d: [X] ", i);
    }
    
    // Choix simple
    printf("\n1. Piocher\n2. Prendre défausse\nChoix: ");
    int choice;
    scanf("%d", &choice);
    
    if(choice == 1 && game->deck_count > 0) {
        Card drawn = game->deck[--game->deck_count];
        printf("Vous avez pioché: %d\n", drawn.value);
        
        printf("Remplacer quelle carte? (0-%d): ", HAND_SIZE-1);
        int card_idx;
        scanf("%d", &card_idx);
        
        // Échange
        game->discard_piles[p][game->discard_counts[p]++] = game->hands[p][card_idx];
        game->hands[p][card_idx] = drawn;
        game->hands[p][card_idx].is_visible = 1;
    }
    // (À compléter pour les autres actions)
    
    game->current_player = (game->current_player + 1) % game->player_count;
}

int check_game_end(GameState* game) {
    for(int p = 0; p < game->player_count; p++) {
        int all_visible = 1;
        for(int c = 0; c < HAND_SIZE; c++) {
            if(!game->hands[p][c].is_visible) {
                all_visible = 0;
                break;
            }
        }
        if(all_visible) return 1;
    }
    return 0;
}