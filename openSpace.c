#include "coordinate.h"
#include "openSpace.h"
#include "game.h"
#include <stdlib.h>

openSpace* buildOpenSpace(char side)
{
    openSpace* myOpenSpace = malloc(sizeof(openSpace*) * 3);
    myOpenSpace->display = 'X';
    myOpenSpace->side = side;
    myOpenSpace->movesLen = 0;
    coordinate** moves = malloc(sizeof(coordinate*));
    moves[0] = NULL;
    myOpenSpace->moves = moves;
    return myOpenSpace;
}

void freeOpenSpace(openSpace* openSpace)
{
    if (openSpace->moves[0] != NULL)
    {
        for (int i = 0; i < (sizeof(openSpace->moves) / sizeof(coordinate*)) + 1; i++)
        free(openSpace->moves[i]);
    }
    free(openSpace->moves);
    free(openSpace);
}