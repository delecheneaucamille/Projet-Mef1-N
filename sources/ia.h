#ifndef IA_H
#define IA_H

#include <stdio.h>
#include <stdlib.h>
#include "player.h"

int getIndexHighestCard(Player *p);
void turnStateCard(Player *p);
void iaTurn(Player *p, Stack *s, Discard *d);

#endif // IA_H
