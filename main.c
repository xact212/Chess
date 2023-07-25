#include "pawn.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    board* mainBoard = buildBoard(8, 8); //creates board struct
    initBoardMatrix(mainBoard, 'n'); //sets each piece for initial configuration
    buildPiece(mainBoard, 'p', 0, 1, 'w');
    buildPiece(mainBoard, 'p', 1, 1, 'w');
    buildPiece(mainBoard, 'p', 2, 1, 'w');
    buildPiece(mainBoard, 'p', 3, 1, 'w');
    buildPiece(mainBoard, 'p', 4, 1, 'w');
    buildPiece(mainBoard, 'p', 5, 1, 'w');
    buildPiece(mainBoard, 'p', 6, 1, 'w');
    buildPiece(mainBoard, 'p', 7, 1, 'w');
    buildPiece(mainBoard, 'r', 0, 0, 'w');
    buildPiece(mainBoard, 'B', 1, 0, 'w');
    buildPiece(mainBoard, 'K', 2, 0, 'w');
    buildPiece(mainBoard, 'q', 3, 0, 'w');
    buildPiece(mainBoard, 'k', 4, 0, 'w');
    buildPiece(mainBoard, 'K', 5, 0, 'w');
    buildPiece(mainBoard, 'B', 6, 0, 'w');
    buildPiece(mainBoard, 'r', 7, 0, 'w');
    printBoard(mainBoard);
    gameLoop('w', mainBoard);
    freeBoard(mainBoard);
    return 0;
}