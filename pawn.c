#include "pawn.h"
#include "game.h"
#include <stdlib.h>
#include <stdbool.h>


pawn* buildPawn()
{
    pawn* myPawn = malloc(sizeof(pawn) * 2);
    myPawn->display = 'p';
    coordinate** moves = malloc(2 * sizeof(coordinate*));
    moves[0] = buildCoordinate(0,1);
    moves[1] = buildCoordinate(0, 2);
    myPawn->moves = moves; //can move up one or two, depends on hasBeenmoved variable for move 2
    myPawn->hasBeenMoved = false;
    return myPawn;
}
