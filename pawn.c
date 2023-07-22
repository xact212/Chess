#include "coordinate.h"
#include "pawn.h"
#include "game.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

pawn* buildPawn(char side)
{
    pawn* myPawn = malloc(sizeof(pawn) * 2);
    myPawn->display = 'p';
    myPawn->side = side;
    myPawn->hasBeenMoved = false;
    myPawn->movesLen = 4;
    coordinate** moves = malloc(myPawn->movesLen * sizeof(coordinate*));
    if (side == 'w')
    {
        moves[0] = buildCoordinate(0,2); //   0
        moves[1] = buildCoordinate(0,1); // 2 1 3
        moves[2] = buildCoordinate(-1,1);//  wp
        moves[3] = buildCoordinate(1,1);
    }
    else if (side == 'b')
    {
        moves[0] = buildCoordinate(0,-2); //  bp
        moves[1] = buildCoordinate(0,-1); // 2 1 3
        moves[2] = buildCoordinate(-1,-1);//   0
        moves[3] = buildCoordinate(1,-1);
    }
    myPawn->moves = moves; //can move up one or two, depends on hasBeenmoved variable for move 2
    return myPawn;
}

