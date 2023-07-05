#ifndef OPENSPACE_H
#define OPENSPACE_H
#include "coordinate.h"
#include <stdbool.h>


typedef struct openSpace{
    char display;
    char side;
    coordinate** moves;
    bool hasBeenMoved;
}openSpace;

openSpace* buildOpenSpace(char side);

void freeOpenSpace(openSpace* openSpace);
#endif