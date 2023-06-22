#include "game.h"

struct coordinate* buildCoordinate(int x, int y)
{
    struct coordinate* myCoordinate = malloc(sizeof(struct coordinate));
    myCoordinate->x = x;
    myCoordinate->y = y;
    return myCoordinate;
}