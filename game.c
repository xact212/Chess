#include "pawn.h"
#include "game.h"
#include "board.h"
#include "coordinate.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//genralized checking fucntion. if input expression is true, we print the success string and return true.
//if false, we return the fail string and return false
bool check(bool expression, char* successStr, char* failStr)
{
    if (expression == true)
    {
        printf("%s\n", successStr);
        return true;
    }
    else  
    {
        printf("%s\n", failStr);
        return false;
    }  
}

bool checkInputSyntax(char* input)
{
    //expecting coordinates to be from 1-8 rather than 0-7. this helps us because
    //atoi returns 0 if input is not integer
    bool inputValid = true;

    //first coordinate syntax evalutaion, expecting: (x1,y1)
    bool firstCoordinateCondition = (input[0] == '(' && (atoi(&input[1]) > 0 && atoi(&input[1]) < 9)  && input[2] == ',' && 
    (atoi(&input[3]) > 0 && atoi(&input[3]) < 9) && input[4] == ')');
    inputValid = check(firstCoordinateCondition, "first coordinate good", "first coordinate bad, please re-enter move");
    
    //second coordinate syntax evalutaion, expecting: _(x2,y2)
    bool secondCoordinateCondition = (input[5] == '_' && input[6] == '(' && (atoi(&input[7]) > 0 && atoi(&input[7]) < 9)  && input[8] == ',' && 
    (atoi(&input[9]) > 0 && atoi(&input[9]) < 9) && input[10] == ')');
    inputValid = check(secondCoordinateCondition, "second coordinate good", "second coordinate bad, please re-enter move");

    return inputValid;
}


void gameLoop(char startingSide, board* mainBoard)
{
    char side = startingSide; //setup starting conditions
    char* currentPiece = "pawn";
    char input[1024] = "0000000000"; //reason for large number is to prevent buffer overflow
    coordinate* first = buildCoordinate(0, 0);
    coordinate* second = buildCoordinate(0, 0);
    coordinate* move = buildCoordinate(0, 0);
    bool moveValid = false;
    bool currentBeenMoved = true;
    while (true)
    {
        moveValid = false;
        //get input from user
        char* intitialPrompt = "Which move would you like to make? (Format: 1st coordinate [space] 2nd coordinate)\n\
        Example to move pawn from 1st coordinate(3,3) to 2nd coordinate(3,4): (3,3)_(3,4)\n\
        Will reprompt if: A: you try to move a piece that isn't yours B: you try to make \n\
        an illegal move C: you try to put a coordinate that isn't on the board\n\0";
        printf("%s", intitialPrompt);
        scanf("%s", &input);

        if (input[0] == 'q') //allow user to quit by exiting main loop
            break;
        if (checkInputSyntax(input) == false)
            continue;
        first->x = atoi(&input[1]) - 1; //reassign coordinates 
        first->y = atoi(&input[3]) - 1;
        second->x = atoi(&input[7]) - 1; //reassign coordinates
        second->y = atoi(&input[9]) - 1;
        //we need to subtract one becasue we start counting at zero, but a human will start counting at one
        //check if piece is on current side
        if (check(side != mainBoard->boardMatrix[first->x][first->y]->side, "Trying to move piece of opposite side", "")) //if white, make sure you are not trying to control black piece
            continue;
            

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
        
        if(check(movesList[0] != NULL, "", "Trying to move open space"))
        {
            for (int i = 0; i < mainBoard->boardMatrix[first->x][first->y]->movesLen; i++)
            {
                //printf("Move: %i X: %i Y: %i\n", i, movesList[i]->x, movesList[i]->y);
                if (move->x == movesList[i]->x && move->y == movesList[i]->y)
                {
                    printf("Move is in moves list for specified piece\n");
                    moveValid = true;
                }
            } 
        }
        if (moveValid == false)
        {
            printf("Move not in moves list\n");
            continue;
        }
        //printf("Move valid: %i\n", moveValid);  
            
        
        //see if check blocks move
        //make move, do not show to player
        //loop through each piece 
        //check if they have a move that would cause check if you were to make this move
        //if invalid, move back. if valid, keep player there

        //check all special cases
        //different piece of same side is on destination square
        
        if (mainBoard->boardMatrix[first->x][first->y]->side == mainBoard->boardMatrix[second->x][second->y]->side)
            continue;
        

        //castling
        //pawn move 2 vs 1
        if ((movesList[0]->x == 0 && movesList[0]->y == 1) || ((movesList[0]->x == 0 && movesList[0]->y == -1))) //is pawn
        {
            if ((mainBoard->boardMatrix[first->x][first->y]->hasBeenMoved && (move->y == 2 || move->y == -2))) //if has been moved and is trying to move 2 spaces
            {
                continue;
            }
            else
            {
                mainBoard->boardMatrix[first->x][first->y]->hasBeenMoved = true; //if hasn't made move before, set it so the pawn cant make it again
            }    
            //capturing
            //code to move a piece should also work for captures, unless piece is a pawn or king
            //if piece we are moving into is not an open space, and we are using our non capture moves, move is invalid
            if (move->x == 0 && mainBoard->boardMatrix[second->x][second->y]->side != 'n')
            {
                    printf("Trying to capture with non-capture move\n");
                    continue;
            }
        }
        //en passant
        //promotion
        //pawns (is first move for 2 space, has enemy diagonal for captures)

        

        //carry out move
        if ((movesList[0]->x == 0 && movesList[0]->y == 1) || ((movesList[0]->x == 0 && movesList[0]->y == -1))) //is pawn
        {
            currentPiece = "pawn";
            currentBeenMoved = mainBoard->boardMatrix[first->x][first->y]->hasBeenMoved;
        }
            
        buildPiece(mainBoard, currentPiece, second->x, second->y, mainBoard->boardMatrix[first->x][first->y]->side); //overwrite destination with the piece at original position
        mainBoard->boardMatrix[second->x][second->y]->hasBeenMoved = currentBeenMoved; //for pawn to check if has moved twice
        buildPiece(mainBoard, "openSpace", first->x, first->y, 'n');
        printBoard(mainBoard);
    
        //change side
        if (side == 'w')
            side = 'b';
        else
            side = 'w';
    }
    free(first);
    free(second);
    free(move);
}