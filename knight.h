#ifndef KNIGHT_H
#define KNIGHT_H
#include "coordinate.h"
#include <stdbool.h>

typedef struct knight{
    char display;
    char side;
    bool hasBeenMoved; 
    int movesLen;
    coordinate** moves; 
}knight;

knight* buildKnight(char side);

#endif