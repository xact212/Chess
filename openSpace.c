#include "openSpace.h"
#include "game.h"
#include <stdlib.h>

openSpace* buildOpenSpace()
{
    openSpace* myOpenSpace = malloc(sizeof(openSpace*) * 2);
    //openSpace* myOpenSpace;
    myOpenSpace->display = 'X';
    coordinate** moves = malloc(sizeof(coordinate*));
    myOpenSpace->moves = moves;
    return myOpenSpace;
}

void freeOpenSpace(openSpace* openSpace)
{
    for (int i = 0; i < (sizeof(openSpace->moves) / sizeof(coordinate*)) + 1; i++)
        free(openSpace->moves[i]);
    free(openSpace->moves);
    free(openSpace);
}