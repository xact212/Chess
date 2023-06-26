#include "board.h"
#include "openSpace.h"
#include "pawn.h"
#include <stdlib.h>
#include <stdio.h>

board* buildBoard(int width, int height)
{
    board* myBoard = malloc(sizeof(board)); 
    myBoard->boardMatrix = malloc(width * sizeof(openSpace**)); //make 2d array pointer
    
    for (int i = 0; i < height; i++) //make array pointers
        myBoard->boardMatrix[i] = malloc(height * sizeof(openSpace*)); 
    myBoard->width = width;
    myBoard->height = height;
    return myBoard;
}

void initBoardMatrix(board* board, char side)
{
    for (int i = 0; i < board->width; i++)
    {
        for (int j = 0; j < board->height; j++)
        {
            board->boardMatrix[i][j] = buildOpenSpace(side); //initialize board by building an open space at every square
        }
    }
}

void printBoard(board* board)
{
    for (int i = 0; i < board->width; i++)
    {
        for (int j = 0; j < board->height; j++)
        {
            printf("%c ", board->boardMatrix[i][j]->display);
        }
        printf("\n");
    }
}

void freeBoard(board* board)
{
    //free smaller subelements first (int arrays->pointer array->boardMatrix pointer->board struct)
    if (board != NULL) 
    {
        if (board->boardMatrix != NULL)
        {
            for (int i = 0; i < board->width; i++) 
            {   
                    for (int j = 0; j < board->height; j++) 
                    {   
                        if (board->boardMatrix[i][j] != NULL)
                            freeOpenSpace(board->boardMatrix[i][j]); //free each array of void pointers
                    }
            }
            for (int i = 0; i < board->width; i++)
            {
                free(board->boardMatrix[i]);
            }
            free(board->boardMatrix); //free array of void pointer pointers
        }
        free(board);
    }
}