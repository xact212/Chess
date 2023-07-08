#include "pawn.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    board* mainBoard = buildBoard(8, 8); //creates board struct
    initBoardMatrix(mainBoard, 'n'); //sets each piece for initial configuration
    buildPiece(mainBoard, 'p', 4, 4, 'w');
    buildPiece(mainBoard, 'p', 4, 5, 'b');
    buildPiece(mainBoard, 'p', 5, 5, 'b');
    buildPiece(mainBoard, 'p', 2, 7, 'b');
    buildPiece(mainBoard, 'k', 6, 6, 'w');
    printBoard(mainBoard);
    gameLoop('w', mainBoard);
    freeBoard(mainBoard);
    return 0;
}