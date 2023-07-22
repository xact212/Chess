#include "king.h"
#include <stdlib.h>
#include <stdbool.h>

king* buildKing(char side) 
{
    king* myKing = malloc(sizeof(king) * 2);
    myKing->display = 'k';
    myKing->side = side;
    myKing->hasBeenMoved = false;
    myKing->movesLen = 8;
    coordinate** moves = malloc(myKing->movesLen * sizeof(coordinate*));
    moves[0] = buildCoordinate(0,-1); //clockwise
    moves[1] = buildCoordinate(-1,-1); // 3 4 5
    moves[2] = buildCoordinate(-1,0);  // 2 k 6
    moves[3] = buildCoordinate(-1,1);  // 1 0 7
    moves[4] = buildCoordinate(0,1);
    moves[5] = buildCoordinate(1,1);
    moves[6] = buildCoordinate(1,0);
    moves[7] = buildCoordinate(1,-1);
    myKing->moves = moves;
    return myKing;
}