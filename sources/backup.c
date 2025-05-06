#include <stdio.h>
#include "card.h"
#include "player.h"
#include "game.h"




// The save function writes the current game state to a binary file.
// It takes a pointer to the GameState structure and the file name as arguments.
// The function serializes the player count, player data, and the current player index into the file.
void save(GameState *gameState, const char *fileName) {
    FILE *f = fopen(fileName, "wb");
    if (f == NULL) {
        printf("Error opening file for backup\n");
        return;
    }

    fwrite(&gameState->playerCount, sizeof(int), 1, f);
    
    for (int i = 0; i < gameState->playerCount; i++) {
        fwrite(gameState->players[i], sizeof(Player), 1, f);
    }

    fwrite(&gameState->currentPlayer, sizeof(int), 1, f);

    fclose(f);
}

// The load function reads the game state from a binary file.
// It takes a pointer to the GameState structure and the file name as arguments.
// The function deserializes the player count, player data, and the current player index from the file.
void load(GameState *gameState, const char *fileName) {
    FILE *f = fopen(fileName, "rb");
    if (f == NULL) {
        printf("Error opening file for loading\n");
        return;
    }

    fread(&gameState->playerCount, sizeof(int), 1, f);
    
    for (int i = 0; i < gameState->playerCount; i++) {
        fread(gameState->players[i], sizeof(Player), 1, f);
    }

    fread(&gameState->currentPlayer, sizeof(int), 1, f);

    fclose(f);
}

int main() {
    Player player1;
    strcpy(player1.name, "Example Name");
    player1.ai = 0;
    player1.score = 0;

    GameState gameState;
    gameState.players = (Player**) malloc(sizeof(Player*));
    gameState.players[0] = &player1;
    gameState.playerCount = 1;
    gameState.currentPlayer = 0;

    save(&gameState, "game.sav");

    strcpy(player1.name, "Wrong Name");

    load(&gameState, "game.sav");

    printf("Player name: %s\nscore: %d\n", player1.name, player1.score);

    free(gameState.players);
    return 0;
}