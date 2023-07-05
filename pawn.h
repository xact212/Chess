#ifndef PAWN_H
#define PAWN_H
#include "coordinate.h"
#include "game.h"
#include <stdbool.h>

typedef struct pawn{
    char display;
    char side;
    coordinate** moves; //array of coordinates represents each valid move disregarding obstacles
    bool hasBeenMoved;
}pawn;

pawn* buildPawn(char side);

#endif