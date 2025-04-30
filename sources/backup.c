#include <stdio.h>
#include <card.h>
#include <player.h>




void save(Player *player, int noPlayers, int Nogame, const char *fileName) {
    FILE *f = fopen(fileName, "wb"); 
    if (f == NULL) {
        printf("Error opening file for backup\n");
        return;
    }
    fwrite(&noPlayers, sizeof(int), 1, f);
    for (int i = 0; i < noPlayers; i++) {
        fwrite(&player[i], sizeof(Player), 1, f);
    }
    fwrite(&Nogame, sizeof(int), 1, f);
    fclose(f);
}

void load(Player *player, int *noPlayers, int *Nogame, const char *fileName) {
    FILE *f = fopen(fileName, "rb");
    if (f == NULL) {
        printf("Error opening file for loading\n");
        return;
    }

    fread(noPlayers, sizeof(int), 1, f);
    for (int i = 0; i < *noPlayers; i++) {
        fread(&player[i], sizeof(Player), 1, f);
    }
    fread(Nogame, sizeof(int), 1, f);
    fclose(f);
}

int main(int argc, char *argv[]) {
    Player player;
    strcpy(player.name, "Example Name");
    player.ai = 0;
    player.hand[0].value = 1; // Assign a value to the card
    strcpy(player.hand[0].state, 0); // Assign a suit to the card
    player.score = 0;

    save(&player, 1, 1, "player.sav");

    // Modification pour tester le chargement
    strcpy(player.name, "Wrong Name");

    load(&player, NULL, NULL, "player.sav");

    printf("Player name: %s\nscore: %d\n", player.name, player.score);
    return 0;
}
