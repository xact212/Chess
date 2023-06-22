#include "openSpace.h"
#include "game.h"
#include <stdlib.h>
struct openSpace* buildOpenSpace()
{
    struct openSpace* myOpenSpace = malloc(sizeof(struct openSpace));
    myOpenSpace->display = 'X';
    struct coordinate moves[0] = {};
    myOpenSpace->moves = moves;
    return myOpenSpace;
}