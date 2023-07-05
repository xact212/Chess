#ifndef OPENSPACE_H
#define OPENSPACE_H
#include "coordinate.h"
#include <stdbool.h>


typedef struct openSpace{
    char display;
    char side;
    bool hasBeenMoved;
    int movesLen;
    coordinate** moves;
}openSpace;

openSpace* buildOpenSpace(char side);

void freeOpenSpace(openSpace* openSpace);
#endif