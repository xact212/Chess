#ifndef OPENSPACE_H
#define OPENSPACE_H
#include "game.h"

typedef struct{
    char display;
    coordinate** moves;
}openSpace;

openSpace* buildOpenSpace();

void freeOpenSpace(openSpace* openSpace);
#endif