#include "rook.h"
#include <stdlib.h>

rook* buildRook(char side) {
    rook* myRook = malloc(sizeof(rook) * 2);
    myRook->display = 'r';
    myRook->side = side;
    myRook->hasBeenMoved = false;
    myRook->movesLen = 28; //7 squares in one direction max * 4 directions = 28 moves
    coordinate** moves = malloc(myRook->movesLen * sizeof(coordinate*));
    for (int i = 0; i < 7; i++) { //left
        int x = -(i + 1);
        moves[i] = buildCoordinate(x, 0);
    }

    for (int i = 0; i < 7; i++) { //up
        int y = (i + 1);
        moves[i + 7] = buildCoordinate(0, y);
    }

    for (int i = 0; i < 7; i++) { //right
        int x = (i + 1);
        moves[i + 14] = buildCoordinate(x, 0);
    }

    for (int i = 0; i < 7; i++) { //down
        int y = -(i + 1);
        moves[i + 21] = buildCoordinate(0, y);
    }
    myRook->moves = moves;
    return myRook;
}

/*
              14
              13
              12
              11
              10
              9
              8
7 6 5 4 3 2 1 r 15 16 17 18 19 20 21      
              22
              23
              24
              25
              26
              27
              28


*/