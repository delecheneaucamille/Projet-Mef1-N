#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "game.h"
#include "card.h"
#include "player.h"
#include "display.h"

int main()
{
    int run = 1;

    while (run == 1)
    {
        system("clear");
        printf("Welcome to the Skyjo card game!\n");
        printf("Loading resources");
        displayLoading();
        createMenu();
        run = selectGameMode();
    }
    printf("Thanks for playing! See you soon.\n");

    return 0;
}