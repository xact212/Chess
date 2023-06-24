#ifndef PAWN_H
#define PAWN_H
#include "game.h"
#include <stdbool.h>

typedef struct {
    char display;
    coordinate** moves; //array of coordinates represents each valid move disregarding obstacles
    bool hasBeenMoved;
}pawn;

pawn* buildPawn();

#endif