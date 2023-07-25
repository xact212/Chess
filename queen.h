#ifndef QUEEN_H
#define QUEEN_H
#include "coordinate.h"
#include "game.h"
#include <stdbool.h>

typedef struct queen{
    char display;
    char side;
    bool hasBeenMoved;
    int movesLen;
    coordinate** moves; //array of coordinates represents each valid move disregarding obstacles
}queen;

queen* buildQueen(char side);

#endif