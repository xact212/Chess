#ifndef PAWN_H
#define PAWN_H
#include "coordinate.h"
#include "game.h"
#include "board.h"
#include <stdbool.h>

typedef struct pawn{
    char display;
    char side;
    bool hasBeenMoved;
    int movesLen;
    coordinate** moves; //array of coordinates represents each valid move disregarding obstacles
}pawn;

pawn* buildPawn(char side);
void promotePawn(coordinate* currentPos, board* board);
bool checkPawn(coordinate* first, coordinate* second, coordinate* move, board* board);

#endif