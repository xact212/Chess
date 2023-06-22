#ifndef BOARD_H
#define BOARD_H

struct board{
    char** boardMatrix; 
    int width;
    int height;
};

struct board* buildBoard(int width, int height);

void printBoard(struct board* board);

void initBoardMatrix(struct board* board);

void freeBoard(struct board* board);
#endif