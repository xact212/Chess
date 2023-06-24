#include "game.h"

coordinate* buildCoordinate(int x, int y)
{
    coordinate* myCoordinate = malloc(sizeof(coordinate));
    myCoordinate->x = x;
    myCoordinate->y = y;
    return myCoordinate;
}