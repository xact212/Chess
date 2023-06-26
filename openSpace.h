#ifndef OPENSPACE_H
#define OPENSPACE_H
#include "coordinate.h"


typedef struct{
    char display;
    coordinate** moves;
    char side;
}openSpace;

openSpace* buildOpenSpace(char side);

void freeOpenSpace(openSpace* openSpace);
#endif