#ifndef OPENSPACE_H
#define OPENSPACE_H
#include "game.h"

struct openSpace{
    char display;
    struct coordinate* moves;
};

struct openSpace* buildOpenSpace();
#endif