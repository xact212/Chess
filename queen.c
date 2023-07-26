#include "queen.h"
#include <stdlib.h>

queen* buildQueen(char side) {
    queen* myQueen = malloc(sizeof(queen) * 2);
    myQueen->display = 'q';
    myQueen->side = side;
    myQueen->hasBeenMoved = false;
    myQueen->movesLen = 56; //7 squares in one direction max * 8 directions = 56 moves
    coordinate** moves = malloc(myQueen->movesLen * sizeof(coordinate*));
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

    for (int i = 0; i < 7; i++) { //up left
        int x = -(i + 1);
        int y = (i + 1);
        moves[i + 28] = buildCoordinate(x, y);
    }

    for (int i = 0; i < 7; i++) { //up right
        int x = (i + 1);
        int y = (i + 1);
        moves[i + 35] = buildCoordinate(x, y);
    }

    for (int i = 0; i < 7; i++) { //down right
        int x = (i + 1);
        int y = -(i + 1);
        moves[i + 42] = buildCoordinate(x, y);
    }

    for (int i = 0; i < 7; i++) { //down left
        int x = -(i + 1);
        int y = -(i + 1);
        moves[i + 49] = buildCoordinate(x, y);
    }
    
    myQueen->moves = moves;
    return myQueen;
}
