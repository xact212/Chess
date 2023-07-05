#include "pawn.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    board* mainBoard = buildBoard(8, 8); //creates board struct
    initBoardMatrix(mainBoard, 'n'); //sets each piece for initial configuration
    buildPiece(mainBoard, "pawn", 4, 4, 'w');
    buildPiece(mainBoard, "pawn", 2, 7, 'b');
    printBoard(mainBoard);
    gameLoop('w', mainBoard);
    freeBoard(mainBoard);
    return 0;
}