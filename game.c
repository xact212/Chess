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

void makeMove(coordinate* first, coordinate* second, board* board, bool currentBeenMoved)
{
    buildPiece(board, board->boardMatrix[first->x][first->y]->display, second->x, second->y, board->boardMatrix[first->x][first->y]->side); //overwrite destination with the piece at original position
    board->boardMatrix[second->x][second->y]->hasBeenMoved = currentBeenMoved; //for pawn to check if has moved twice
    buildPiece(board, 'X', first->x, first->y, 'n');
    //printBoard(board);
}
/*
This fucntion is designed to check if any given move you make will put your own king in check.
The general idea of this function is as follows:
1. make the move
2. make sure there is no opposing piece that is now attacking your king
3. if there is undo the move
*/
bool moveCausesCheck(coordinate* first, coordinate* second, board* board, char currentSide, bool currentBeenMoved)
{
    //assume all other checks have been made first, always put this last in checking order
    //make move
    coordinate* captureList[50];
    for (int i = 0; i < 50; i++) {captureList[i] = buildCoordinate(0,0);}
    int currMoveX = 0;
    int currMoveY = 0;
    //need to know this information so we can undo the move if needed
    bool secondhasBeenMoved = board->boardMatrix[second->x][second->y]->hasBeenMoved; 
    char secondDisplay = board->boardMatrix[second->x][second->y]->display;
    char secondSide = board->boardMatrix[second->x][second->y]->side;
    makeMove(first, second, board, currentBeenMoved); //make move, undo as neccesary
    //loop through every single piece 
    for (int i = 0; i < board->width; i++)
    {
        for (int j = 0; j < board->height; j++)
        {
            //if it is a piece on the opposite side, and has a move in moveslist that puts the king in check,
            //the move in invalid and we return false and undo move
            
            if (board->boardMatrix[i][j]->side != currentSide && board->boardMatrix[i][j]->side != 'n') //if not oppoosite side we don't care about its moves
            {
                //need to account for special case if a pawn, non capturing moves do no count for check
                if (board->boardMatrix[i][j]->display == 'p') //if pawn, only use last two moves in the moves list becasue these are its capture moves
                {
                    printf("i: %i j: %i\n", i, j);
                    captureList[0]->x = board->boardMatrix[i][j]->moves[2]->x;
                    captureList[0]->y = board->boardMatrix[i][j]->moves[2]->y;
                    captureList[1]->x = board->boardMatrix[i][j]->moves[3]->x;
                    captureList[1]->y = board->boardMatrix[i][j]->moves[3]->y;
                }
                else //every other piece can capture with any move
                {
                    for (int move = 0; move < board->boardMatrix[i][j]->movesLen; move++) {
                        captureList[move]->x = board->boardMatrix[i][j]->moves[move]->x;
                        captureList[move]->y = board->boardMatrix[i][j]->moves[move]->y;
                    }
                }
                //loop through capture list and check if it has a move that could capture your king
                for (int move = 0; move < board->boardMatrix[i][j]->movesLen; move++)
                {
                    currMoveX = i + captureList[move]->x; //set hypothetical move relative to current piece position
                    currMoveY = j + captureList[move]->y;
                    //if current side's king is in check now, we need to undo the move and return true
                    if (board->boardMatrix[currMoveX][currMoveY]->display == 'k' && board->boardMatrix[currMoveX][currMoveY]->side == currentSide) 
                    {
                        makeMove(second, first, board, currentBeenMoved); //move whatever is at destination square back
                        buildPiece(board, secondDisplay, second->x, second->y, secondSide); //make copy of what used to be at second at second square again
                        board->boardMatrix[second->x][second->y]->hasBeenMoved = secondhasBeenMoved;
                        for (int space = 0; space < 50; space++){free(captureList[space]);}
                        printf("Move puts king in check\n");
                        return true;
                    }
                }
            }
            
        }
    }
    for (int space = 0; space < 50; space++){free(captureList[space]);}
    printf("Move does not put king in check\n");
    return false; //if we get to the end without problem we can safely return false
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
                printf("Move: %i X: %i Y: %i\n", i, movesList[i]->x, movesList[i]->y);
                if (move->x == movesList[i]->x && move->y == movesList[i]->y)
                {
                    printf("Move is in moves list for specified piece\n");
                    moveValid = true;
                    break;
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
        if ((movesList[0]->x == 0 && movesList[0]->y == 2) || ((movesList[0]->x == 0 && movesList[0]->y == -2))) //is pawn
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
            if ((move->x == 1 || move->x == -1) && mainBoard->boardMatrix[second->x][second->y]->moves[0] == NULL)
            {
                printf("Trying to capture open space\n");
                continue;   
            }
        }
        //en passant
        //promotion
        //pawns (is first move for 2 space, has enemy diagonal for captures)
        
        //see if check prevents move
        if (moveCausesCheck(first, second, mainBoard, side, mainBoard->boardMatrix[first->x][first->y]->hasBeenMoved))
        {
            continue;
        }
                    
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