#include <stdio.h>
#include <card.h>

void backup(Player *player,int noPlayers, int Nogame, const char *fileName ){
FILE *f= fopen(fileName,"wb"); // open a file to write the infos in 
if (f==NULL){
    printf("Error opening file for backup");
    return;
}
fwrite(&noPlayers,sizeof(int),1,f);
for (int i = 0; i < noPlayers; i++) {
    fwrite(&player[i], sizeof(Player), 1, f);
}
fwrite(&Nogame,sizeof(int),1,f);


fclose(f);
}