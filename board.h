#ifndef BOARD_H
#define BOARD_H
#include "openSpace.h"

typedef struct{
    openSpace*** boardMatrix; 
    int width;
    int height;
}board;

board* buildBoard(int width, int height);

void printBoard(board* board);

void initBoardMatrix(board* board);

void freeBoard(board* board);
#endif