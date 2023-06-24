#include "openSpace.h"
#include "game.h"
#include <stdlib.h>

openSpace* buildOpenSpace()
{
    openSpace* myOpenSpace = malloc(sizeof(openSpace*) * 2);
    //openSpace* myOpenSpace;
    myOpenSpace->display = 'X';
    coordinate** moves = malloc(sizeof(coordinate**));
    myOpenSpace->moves = moves;
    return myOpenSpace;
}

void freeOpenSpace(openSpace* openSpace)
{
    free(openSpace->moves);
    free(openSpace);
}