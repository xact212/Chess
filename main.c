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
    buildPiece(mainBoard, 'r', 2, 2, 'b');
    buildPiece(mainBoard, 'r', 6, 7, 'b');
    buildPiece(mainBoard, 'r', 5, 7, 'b');
    buildPiece(mainBoard, 'r', 4, 7, 'b');
    buildPiece(mainBoard, 'r', 3, 7, 'b');
    buildPiece(mainBoard, 'r', 1, 1, 'b');
    printBoard(mainBoard);
    gameLoop('w', mainBoard);
    freeBoard(mainBoard);
    return 0;
}