#ifndef ROOK_H
#define ROOK_H
#include "coordinate.h"
#include "game.h"
#include <stdbool.h>

typedef struct rook{
    char display;
    char side;
    bool hasBeenMoved;
    int movesLen;
    coordinate** moves; //array of coordinates represents each valid move disregarding obstacles
}rook;

rook* buildRook(char side);

#endif