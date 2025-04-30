#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 

#define DECK_SIZE 52

typedef struct
{
    int score;
    char *name;
    int ai; // 0 = player , 1 = AI player
    Card *hand;
    int sizeHand;
} Player;

    typedef struct {
        Card* pile;      // Tableau dynamique pour la défausse
        int count;       // Nombre de cartes actuellement dans la défausse
        int capacity;    // Taille maximale allouée
    } Defausse;

    typedef struct
    {
        int value;
        int state;
    } Card;
    
    typedef struct {
        Player players; // Tableau dynamique pour les mains des joueurs
        int currentPlayer;   // Indice du joueur courant
        Defausse defausse;   // Pile de défausse
    } GameState;




void init_game(GameState* game, Player players, int min_val, int max_val) {
    game->player_count = players;
    game->current_player = 0;
    game->deck_count = DECK_SIZE;

    // Initialisation simple du deck
    for(int i = 0; i < DECK_SIZE; i++) {
        game->deck[i].value = (rand() % (max_val - min_val + 1)) + min_val;
        game->deck[i].is_visible = 0;
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