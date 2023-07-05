#include "board.h"
#include "openSpace.h"
#include "pawn.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
    for (int i = board->width - 1; i >= 0; i--)
    {
        for (int j = 0; j < board->height; j++)
        {
            printf("%c%c ",board->boardMatrix[j][i]->side, board->boardMatrix[j][i]->display);
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

void buildPiece(board* board, char *piece, int x, int y, char side) //allows each piece's data to be properly accessed externally
{
    freeOpenSpace(board->boardMatrix[x][y]);
    if (strcmp(piece, "pawn") == 0)
    {
        board->boardMatrix[x][y] = buildPawn(side);
        return;
    }
    else if (strcmp(piece, "openSpace") == 0)
    {
        board->boardMatrix[x][y] = buildOpenSpace(side);
        return;
    }
    else    
    {
        printf("No piece specified, creating open space");
        board->boardMatrix[x][y] = buildOpenSpace(side);
        return;
    }
}

