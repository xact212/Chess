#include "pawn.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    board* mainBoard = buildBoard(8, 8);
    initBoardMatrix(mainBoard, 'n');
    freeOpenSpace(mainBoard->boardMatrix[4][5]);
    mainBoard->boardMatrix[4][5] = buildPawn('w');
    printBoard(mainBoard);
    gameLoop('w', mainBoard);
    freeBoard(mainBoard);
    return 0;
}