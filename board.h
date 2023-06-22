#ifndef BOARD_H
#define BOARD_H
#include "openSpace.h"

struct board{
    struct openSpace*** boardMatrix; 
    int width;
    int height;
};

struct board* buildBoard(int width, int height);

void printBoard(struct board* board);

void initBoardMatrix(struct board* board);

void freeBoard(struct board* board);
#endif