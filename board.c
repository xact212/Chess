#include "board.h"
#include "openSpace.h"
#include <stdlib.h>
#include <stdio.h>

struct board* buildBoard(int width, int height)
{
    struct board* myBoard = malloc(sizeof(struct board));
    //build 2d array of void*s
    myBoard->boardMatrix = (struct openSpace***)malloc(width * sizeof(struct openSpace**)); //make array of void pointer pointers
    for (int i = 0; i < height; i++)
        myBoard->boardMatrix[i] = (struct openSpace**)malloc(height * sizeof(struct openSpace**)); //make array of void pointers
    
    myBoard->width = width;
    myBoard->height = height;
    return myBoard;
}

void initBoardMatrix(struct board* board)
{
    for (int i = 0; i < board->width; i++)
    {
        for (int j = 0; j < board->height; j++)
        {
            board->boardMatrix[i][j] = buildOpenSpace(); //initialize board by typcasting each void* to an openSpace struct
        }
    }
}

void printBoard(struct board* board)
{
    for (int i = 0; i < board->width; i++)
    {
        for (int j = 0; j < board->height; j++)
        {
            printf("%c ", (struct openSpace*)board->boardMatrix[i][j]->display);
        }
        printf("\n");
    }
}

void freeBoard(struct board* board)
{
    //free smaller subelements first (int arrays->pointer array->boardMatrix pointer->board struct)
    if (board != NULL) 
    {
        if (board->boardMatrix != NULL)
        {
            for (int i = 0; i < board->width; i++) 
            {   
            if (board->boardMatrix[i] != NULL)
                free(board->boardMatrix[i]); //free each array of void pointers
            }
            free(board->boardMatrix); //free array of void pointer pointers
        }
        free(board);
    }
}