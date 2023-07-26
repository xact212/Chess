#include "bishop.h"
#include <stdlib.h>

bishop* buildBishop(char side) {
    bishop* myBishop = malloc(sizeof(bishop) * 2);
    myBishop->display = 'B';
    myBishop->side = side;
    myBishop->hasBeenMoved = false;
    myBishop->movesLen = 28; //7 squares in one direction max * 4 directions = 28 moves
    coordinate** moves = malloc(myBishop->movesLen * sizeof(coordinate*));
    for (int i = 0; i < 7; i++) { //up left
        int x = -(i + 1);
        int y = (i + 1);
        moves[i] = buildCoordinate(x, y);
    }

    for (int i = 0; i < 7; i++) { //up right
        int x = (i + 1);
        int y = (i + 1);
        moves[i + 7] = buildCoordinate(x, y);
    }

    for (int i = 0; i < 7; i++) { //down right
        int x = (i + 1);
        int y = -(i + 1);
        moves[i + 14] = buildCoordinate(x, y);
    }

    for (int i = 0; i < 7; i++) { //down left
        int x = -(i + 1);
        int y = -(i + 1);
        moves[i + 21] = buildCoordinate(x, y);
    }
    myBishop->moves = moves;
    return myBishop;
}

/*

 7              14
  6            13
   5          12
    4        11
     3      10
      2    9
       1  8 
         b
      22  15
     23     16
    24       17
   25         18 
  26           19
 27             20
28                21

*/