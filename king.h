#ifndef KING_H
#define KING_H
#include "coordinate.h"
#include <stdbool.h>

typedef struct king{
    char display;
    char side;
    bool hasBeenMoved; //repurposed for castling
    int movesLen;
    coordinate** moves; 
}king;

king* buildKing(char side);

#endif