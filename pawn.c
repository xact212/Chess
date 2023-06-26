#include "coordinate.h"
#include "pawn.h"
#include "game.h"
#include <stdlib.h>
#include <stdbool.h>


pawn* buildPawn(char side)
{
    pawn* myPawn = malloc(sizeof(pawn) * 2);
    myPawn->display = 'p';
    myPawn->hasBeenMoved = false;
    myPawn->side = side;
    coordinate** moves = malloc(2 * sizeof(coordinate*));
    moves[0] = buildCoordinate(0,1);
    moves[1] = buildCoordinate(0, 2);
    myPawn->moves = moves; //can move up one or two, depends on hasBeenmoved variable for move 2
    return myPawn;
}
