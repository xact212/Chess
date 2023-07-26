#ifndef BOARD_H
#define BOARD_H
#include "openSpace.h"

typedef struct board{
    openSpace*** boardMatrix; 
    int width;
    int height;
}board;

board* buildBoard(int width, int height);

void printBoard(board* board);

void initBoardMatrix(board* board, char side);

void freeBoard(board* board);

void buildPiece(board* board, char piece, int x, int y, char side);
#endif