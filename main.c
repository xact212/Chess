#include "pawn.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct board* mainBoard = buildBoard(8, 8);
    initBoardMatrix(mainBoard);
    printBoard(mainBoard);
    freeBoard(mainBoard);
    return 0;
}