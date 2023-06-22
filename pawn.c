#include "pawn.h"
#include "game.h"
#include <stdlib.h>
#include <stdbool.h>


struct pawn* buildPawn()
{
    struct pawn* myPawn = malloc(sizeof(struct pawn));
    myPawn->display = 'p';
    struct coordinate* moves[2] = {buildCoordinate(0, 1), buildCoordinate(0, 2)};
    myPawn->moves = moves; //can move up one or two, depends on hasBeenmoved variable for move 2
    myPawn->hasBeenMoved = false;
    return myPawn;
}