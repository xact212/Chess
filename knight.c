#include "knight.h"
#include <stdlib.h>
#include <stdbool.h>

knight* buildKnight(char side) 
{
    knight* myKnight = malloc(sizeof(knight) * 2);
    myKnight->display = 'K';
    myKnight->side = side;
    myKnight->hasBeenMoved = false;
    myKnight->movesLen = 8;
    coordinate** moves = malloc(myKnight->movesLen * sizeof(coordinate*));
    moves[0] = buildCoordinate(1,2); //clockwise
    moves[1] = buildCoordinate(2,1);   //    7 0
    moves[2] = buildCoordinate(2,-1);  //   6   1
    moves[3] = buildCoordinate(1,-2);  //     K 
    moves[4] = buildCoordinate(-1,-2); //   5   2
    moves[5] = buildCoordinate(-2,-1); //    4 3
    moves[6] = buildCoordinate(-2,1);
    moves[7] = buildCoordinate(-1,2);
    myKnight->moves = moves;
    return myKnight;
}