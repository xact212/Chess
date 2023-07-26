#ifndef BISHOP_H
#define BISHOP_H
#include "coordinate.h"
#include "game.h"
#include <stdbool.h>

typedef struct bishop{
    char display;
    char side;
    bool hasBeenMoved;
    int movesLen;
    coordinate** moves; //array of coordinates represents each valid move disregarding obstacles
}bishop;

bishop* buildBishop(char side);

#endif