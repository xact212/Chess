#include "pawn.h"
#include "game.h"
#include "board.h"
#include "coordinate.h"
#include <stdlib.h>
#include <stdio.h>

void gameLoop(char startingSide, board* mainBoard)
{
    char side = startingSide;
    char input[999] = "0000000000"; //reason for large number is to prevent buffer overflow
    coordinate* first = buildCoordinate(0, 0);
    coordinate* second = buildCoordinate(0, 0);
    coordinate* move = buildCoordinate(0, 0);
    //while (1)
    //{
        //get input from user
        printf("Which move would you like to make? (Format: 1st coordinate [space] 2nd coordinate)\n");
        printf("Example to move pawn from 1st coordinate(3,3) to 2nd coordinate(3,4): (3,3)_(3,4)\n");
        printf("Will reprompt if: A: you try to move a piece that isn't yours B: you try to make "
        "an illegal move C: you try to put a coordinate that isn'n on the board\n");
        scanf("%s", &input);

        //check if valid
        //expecting coordinates to be from 1-8 rather than 0-7. this helps us because
        //atoi returns 0 if input is not integer

        //REFACTOR SYNATX EVALUTATION INTO ONE FUNCTION
        //first coordinate syntax evalutaion
        if (input[0] == '(' && (atoi(&input[1]) > 0 && atoi(&input[1]) < 9)  && input[2] == ',' && 
        (atoi(&input[3]) > 0 && atoi(&input[3]) < 9) && input[4] == ')') 
        {
            printf("first coordinate good\n");
            first->x = atoi(&input[1]); //reassign coordinates
            first->y = atoi(&input[3]);
        }
        else
        {
            printf("first coordinate bad, please re-enter move\n");
        }

        //second coordinate syntax evalutaion
        if (input[5] == '_' && input[6] == '(' && (atoi(&input[7]) > 0 && atoi(&input[7]) < 9)  && input[8] == ',' && 
        (atoi(&input[9]) > 0 && atoi(&input[9]) < 9) && input[10] == ')')
        {
            printf("second coordinate good\n"); 
            second->x = atoi(&input[7]); //reassign coordinates
            second->y = atoi(&input[9]);
        }
        else
        {
            printf("second coordinate bad, please re-enter move\n");
        }
        //check if input coordinates are in moves list
        coordinate** movesList = mainBoard->boardMatrix[first->x][first->y]->moves;
        /*
        moves are determined by the difference of the second coordinate relative
        to the first. for example, (2,2)_(2,3) would correspond to moving the 
        piece at (2,2) to (2,3), which consists of a change of one in the y
        direction, so the move coordinate for this play would be (0,1).
        if the piece at the first coordinate has a move in its move list that matches
        with the move we just input, we passed the first phase of testing the move.
        loop through moves list, and compare each move to the move the player just made
        */
        move->x = second->x - first->x;
        move->y = second->y - first->y;
        if(movesList[0] != NULL)
        {
            for (int i = 0; i < sizeof(movesList) / sizeof(coordinate*); i++)
            {
                if (move->x == movesList[i]->x && move->y == movesList[i]->y)
                {
                    printf("Move is valid for specified piece\n");
                }
            } 
        }
        
        //check if check blocks move
        //check all special cases

        //carry out move
        freeOpenSpace(mainBoard->boardMatrix[second->x][second->y]); //delete whatever destination used to be
        //mainBoard->boardMatrix[second->x][second->y] = (openSpace*) buildOpenSpace('n'); //make destination open space so there are no casting issues
        mainBoard->boardMatrix[second->x][second->y] = buildPawn('w'); //overwrite destination with the piece at original destination
        freeOpenSpace(mainBoard->boardMatrix[first->x][first->y]); //delete and overwrite origin with open space;
        mainBoard->boardMatrix[first->x][first->y] = (openSpace*) buildOpenSpace('n'); 
        printBoard(mainBoard);
    //}
    free(first);
    free(second);
    free(move);
}