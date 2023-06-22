#include "board.h"
#include <stdlib.h>
#include <stdio.h>

struct board* buildBoard(int width, int height)
{
    struct board* myBoard = malloc(sizeof(struct board));
    myBoard->boardMatrix = (int**)malloc(width * sizeof(int*)); //make array of int pointers
    for (int i = 0; i < height; i++)
        myBoard->boardMatrix[i] = (int*)malloc(height * sizeof(int)); //make array of ints
    myBoard->width = width;
    myBoard->height = height;
    return myBoard;
}

void initBoardMatrix(struct board* board)
{
    printf("width: %i\n", board->width);
    printf("height: %i\n", board->height);
    for (int i = 0; i < board->width; i++)
    {
        printf("i: %i\n", i);
        for (int j = 0; j < board->height; j++)
        {
            printf("j: %i ", j);
            //if (board->boardMatrix[i][j] != NULL)
            board->boardMatrix[i][j] = 0;
        }
    }
}

void printBoard(struct board* board)
{
    printf("width: %i\n", board->width);
    printf("height: %i\n", board->height);
    
    for (int i = 0; i < board->width; i++)
    {
        for (int j = 0; j < board->height; j++)
        {
            printf("%i ", board->boardMatrix[i][j]);
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
                free(board->boardMatrix[i]); //free each array of ints
            }
            free(board->boardMatrix); //free array of int pointers
        }
        free(board);
    }
}