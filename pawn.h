#ifndef PAWN_H
#define PAWN_H
#include "coordinate.h"
#include "game.h"
#include <stdbool.h>

typedef struct {
    char display;
    coordinate** moves; //array of coordinates represents each valid move disregarding obstacles
    bool hasBeenMoved;
    char side;
}pawn;

pawn* buildPawn(char side);

#endif