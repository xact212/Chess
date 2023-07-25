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
    if (!inputValid) {return false;}

    //second coordinate syntax evalutaion, expecting: _(x2,y2)
    bool secondCoordinateCondition = (input[5] == '_' && input[6] == '(' && (atoi(&input[7]) > 0 && atoi(&input[7]) < 9)  && input[8] == ',' && 
    (atoi(&input[9]) > 0 && atoi(&input[9]) < 9) && input[10] == ')');
    return check(secondCoordinateCondition, "second coordinate good", "second coordinate bad, please re-enter move");
}

//conditionally loop through all squares in current direction and return false if a space is not an
//open space
// q u w
// l   r
// a d s
bool tracePath(coordinate* first, coordinate* second, coordinate* move, board* board, char straightOrDiagonal, char direction)
{
    coordinate* currSpace = buildCoordinate(first->x, first->y);
    //s == straight, d == diagonal
    if (straightOrDiagonal == 's') //check for movement in straight lines
    {
        switch (direction)
        {
            case 'u' : //up
            {
                currSpace->y++;
                while (currSpace->y < second->y) //assume already checked for being out of bounds of board
                { //if current square not open space path is invalid
                    if (board->boardMatrix[currSpace->x][currSpace->y]->display != 'X') 
                    {
                        free(currSpace);
                        return false;
                    }
                    currSpace->y++;
                }
                free(currSpace);
                return true; 
            }
            case 'r' : //right
            {
                currSpace->x++;
                while(currSpace->x < second->x) 
                {
                    if (board->boardMatrix[currSpace->x][currSpace->y]->display != 'X') 
                    {
                        free(currSpace);
                        return false;
                    }
                    currSpace->x++;
                }
                free(currSpace);
                return true;
            }
            case 'd' : //down
            {
                currSpace->y--;
                while(currSpace->y > second->y) 
                {
                    if (board->boardMatrix[currSpace->x][currSpace->y]->display != 'X') 
                    {
                        free(currSpace);
                        return false;
                    }
                    currSpace->y--;
                }
                free(currSpace);
                return true;
            }   
            case 'l' : //left
            {
                currSpace->x--;
                while(currSpace->x > second->x) 
                {
                    if (board->boardMatrix[currSpace->x][currSpace->y]->display != 'X') 
                    {
                        free(currSpace);
                        return false;
                    }
                    currSpace->x--;
                }
                free(currSpace);
                return true;
            }
            default :
            {
                puts("No direction specified, checking up");  
                while (currSpace->y < second->y) 
                { 
                    currSpace->y++;
                    if (board->boardMatrix[currSpace->x][currSpace->y]->display != 'X') 
                    {
                        free(currSpace);
                        return false;
                    }
                }
                free(currSpace);
                return true; 
            }
                
        }
    }
    else if (straightOrDiagonal == 'd') //checks for movement in diagonal lines
    {
        switch (direction)
        {
            case 'q' : //up right
            {
                currSpace->x++;
                currSpace->y++;
                while (currSpace->x < second->x && currSpace->y < second->y)
                {
                    if (board->boardMatrix[currSpace->x][currSpace->y]->display != 'X') 
                    {
                        free(currSpace);
                        return false;
                    }
                    currSpace->x++;
                    currSpace->y++;
                }
                free(currSpace);
                return true; 
            }
            case 'w' : //down right
            {
                currSpace->x++;
                currSpace->y--;
                while (currSpace->x < second->x && currSpace->y > second->y)
                {
                    if (board->boardMatrix[currSpace->x][currSpace->y]->display != 'X') 
                    {
                        free(currSpace);
                        return false;
                    }
                    currSpace->x++;
                    currSpace->y--;
                }
                free(currSpace);
                return true; 
            }
            case 'a' : //down left
            {
                currSpace->x--;
                    currSpace->y--;
                while (currSpace->x > second->x && currSpace->y > second->y)
                {
                    
                    if (board->boardMatrix[currSpace->x][currSpace->y]->display != 'X') 
                    {
                        free(currSpace);
                        return false;
                    }
                    currSpace->x--;
                    currSpace->y--;
                }
                free(currSpace);
                return true; 
            }
            case 's' : //up left
            {
                currSpace->x--;
                currSpace->y++;
                while (currSpace->x > second->x && currSpace->y < second->y)
                {
                    if (board->boardMatrix[currSpace->x][currSpace->y]->display != 'X') 
                    {
                        free(currSpace);
                        return false;
                    }
                    currSpace->x--;
                    currSpace->y++;
                }
                free(currSpace);
                return true; 
            }
        }
    }
    return true;
}

bool pathCheckBishop(coordinate* first, coordinate* second, coordinate* move, board* board)
{
    if (move->x < 0 && move->y > 0) //moving up left
    {
        return tracePath(first, second, move, board, 'd', 'q');
    }
    else if (move->x > 0 && move->y > 0) //moving up right
    {
        return tracePath(first, second, move, board, 'd', 'w');
    }
    else if (move->x > 0 && move->y < 0) //moving down right
    {
        return tracePath(first, second, move, board, 'd', 's');
    }
    else if (move->x < 0 && move->y < 0) //moving down left
    {
        return tracePath(first, second, move, board, 'd', 'a');
    }
    return true; //for queen, uses function but doesn't neccesarily move on two axis at a time
}

bool pathCheckRook(coordinate* first, coordinate* second, coordinate* move, board* board)
{
    if (move->x == 0 && move->y > 0) //moving up
    {
        return tracePath(first, second, move, board, 's', 'u');
    }
    else if (move->x > 0 && move->y == 0) //moving right
    {
        return tracePath(first, second, move, board, 's', 'r');
    }
    else if (move->x == 0 && move->y < 0) //moving down
    {
        return tracePath(first, second, move, board, 's', 'd');
    }
    else if (move->x < 0 && move->y == 0) //moving left
    {
        return tracePath(first, second, move, board, 's', 'l');
    }
    return true; //for queen, uses function but doesn't neccesarily move on one axis at a time
}

//checks path of pieces like bishop, rook and queen that have multiple squares they can occupy. 
//
bool pathIsValid(coordinate* first, coordinate* second, coordinate* move, board* board)
{
    switch(board->boardMatrix[first->x][first->y]->display)
    {
        case 'r' :
        {
            if (!pathCheckRook(first, second, move, board))
            {
                //puts("Trying to move rook through other piece!");
                return false;
            }
            return true;
        }
            
        case 'b' :
            if (!pathCheckBishop(first, second, move, board))
            {
                //puts("Trying to move bishop through other piece!");
                return false;
            }
            return true;
        case 'q' : //a queen is really just a combination of a rook and a bishop, so refactoring into different function is uneccesary
            if (!pathCheckRook(first, second, move, board) || !pathCheckBishop(first, second, move, board))
            {
                //puts("Trying to move queen through other piece!");
                return false;
            }
            return true;
        default :
            return true;
    }
}

void makeMove(coordinate* first, coordinate* second, board* board, bool currentBeenMoved)
{
    buildPiece(board, board->boardMatrix[first->x][first->y]->display, second->x, second->y, board->boardMatrix[first->x][first->y]->side); //overwrite destination with the piece at original position
    board->boardMatrix[second->x][second->y]->hasBeenMoved = currentBeenMoved; //for pawn to check if has moved twice
    buildPiece(board, 'X', first->x, first->y, 'n');
    //printBoard(board);
}

bool sideInCheck(board* board, char side)  {
    coordinate* first = buildCoordinate(0,0);
    coordinate* second = buildCoordinate(0,0);
    char oppositeSide = (side == 'w') ? 'b':'w';
    //loop through every piece on board
    for (int i = 0; i < board->width; i++) {
        for (int j = 0; j < board->height; j++) {
            //if opposing side loop through each of their moves
            if (board->boardMatrix[i][j]->side == oppositeSide) {
                first->x = i;
                first->y = j;
                for (int move = 0; move < board->boardMatrix[i][j]->movesLen; move++) {
                    second->x = first->x + board->boardMatrix[i][j]->moves[move]->x;
                    second->y = first->y + board->boardMatrix[i][j]->moves[move]->y;
                    if (second->x < 0 || second->x > 7 || second->y < 0 || second->y > 7) {continue;}
                    //see if each move puts your current king in check
                    bool isKing = board->boardMatrix[second->x][second->y]->display == 'k';
                    bool isCurrSide = board->boardMatrix[second->x][second->y]->side == side;
                    bool kingInCheck = isKing && isCurrSide;
                    if (kingInCheck) {
                        printf("Side :%c is in check\n", side);
                        free(first);
                        free(second);
                        return true;
                    }
                }
            }
        }
    }
    //if none of them do, we are not in check
    printf("Side :%c is not in check\n", side);
    free(first);
    free(second);
    return false;
}

bool canPerformCastle(coordinate* first, coordinate* second, coordinate* move, board* board)
{
    move->x = second->x - first->x;
    move->y = second->y - first->y;
    //must be the same side
    bool sameSide = board->boardMatrix[first->x][first->y]->side == board->boardMatrix[second->x][second->y]->side;
    //either origin needs to be rook and destination needs to be king
    bool rookKing = board->boardMatrix[first->x][first->y]->display == 'r' && board->boardMatrix[second->x][second->y]->display == 'k';
    //or origin needs to be king and destination needs to be rook
    bool kingRook = board->boardMatrix[first->x][first->y]->display == 'k' && board->boardMatrix[second->x][second->y]->display == 'r';
    bool areValidPieces = sameSide && (rookKing || kingRook);
    //check path of rook in direction of king. if no collisions are detected, we can castle
    bool noCollisions = pathCheckRook(first, second, move, board);
    //neither can have castled before
    bool anyBeenCastled = board->boardMatrix[first->x][first->y]->hasBeenMoved || board->boardMatrix[second->x][second->y]->hasBeenMoved;
    if (noCollisions && areValidPieces && !anyBeenCastled)
        return true;
    return false;
}

void performCastle(coordinate* first, coordinate* second, board* board)
{
    char displayTemp = board->boardMatrix[second->x][second->y]->display;
    char side = board->boardMatrix[second->x][second->y]->side;
    if (displayTemp == 'r') //if rook make rook at destination and king at origin
    {
        buildPiece(board, 'k', second->x, second->y, side);
        board->boardMatrix[second->x][second->y]->hasBeenMoved = true;
        buildPiece(board, 'r', first->x, first->y, side);
        board->boardMatrix[first->x][first->y]->hasBeenMoved = true;
    }
    else if (displayTemp == 'k')
    {
        buildPiece(board, 'r', second->x, second->y, side);
        board->boardMatrix[second->x][second->y]->hasBeenMoved = true;
        buildPiece(board, 'k', first->x, first->y, side);
        board->boardMatrix[first->x][first->y]->hasBeenMoved = true;
    }
}

bool moveIsValid(coordinate* first, coordinate* second, coordinate* move, board* board, char side, bool keepMove) 
{
    bool moveValid = false;
    bool currentBeenMoved = true;
    //check if piece is on current side
    //printf("Side: %c\n", side);
    //printf("Piece side: %c\n", board->boardMatrix[first->x][first->y]->side);
    if (side != board->boardMatrix[first->x][first->y]->side) //if white, make sure you are not trying to control black piece
    {
        //printf("Trying to move piece of opposite side\n");
        return false;
    }

    //check if input coordinates are in moves list
    coordinate** movesList = board->boardMatrix[first->x][first->y]->moves;
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
        for (int i = 0; i < board->boardMatrix[first->x][first->y]->movesLen; i++)
        {
            //printf("Move: %i X: %i Y: %i\n", i, movesList[i]->x, movesList[i]->y);
            if (move->x == movesList[i]->x && move->y == movesList[i]->y)
            {
                //printf("Move is in moves list for specified piece\n");
                moveValid = true;
                break;
            }
        } 
    }
    if (moveValid == false)
    {
        //printf("Move not in moves list\n");
        return false;
    }
    //printf("Move valid: %i\n", moveValid);  
        
    
    //see if check blocks move
    //make move, do not show to player
    //loop through each piece 
    //check if they have a move that would cause check if you were to make this move
    //if invalid, move back. if valid, keep player there

    //check all special cases
    //different piece of same side is on destination square
    
    if (second->x < 0 || second->x > 7 || second->y < 0 || second->y > 7) {return false;}
    if (board->boardMatrix[first->x][first->y]->side == board->boardMatrix[second->x][second->y]->side) {return false;}
    if (!pathIsValid(first, second, move, board)) {return false;}
    
    //castling
    //pawn move 2 vs 1
    if (board->boardMatrix[first->x][first->y]->display == 'p') //is pawn
    {
        if (!checkPawn(first, second, move, board)) 
            return false;
    }

    //en passant
    //promotion
    //pawns (is first move for 2 space, has enemy diagonal for captures)

    //see if check prevents move
    if (moveCausesCheck(first, second, board, side, board->boardMatrix[first->x][first->y]->hasBeenMoved, keepMove))
        return false;
    
    return true;
}

bool sideCanMove(board* board, char side) 
{
    coordinate* first = buildCoordinate(0,0);
    coordinate* second = buildCoordinate(0,0);
    coordinate* move = buildCoordinate(0,0);
    for (int i = 0; i < board->width; i++) //loop through each piece on specified side
    {
        for (int j = 0; j < board->width; j++) 
        {
            if (board->boardMatrix[i][j]->side == side) 
            { //loop through each move in piece
                for (int currMove = 0; currMove < board->boardMatrix[i][j]->movesLen; currMove++) 
                {
                    first->x = i;
                    first->y = j;
                    second->x = first->x + board->boardMatrix[i][j]->moves[currMove]->x;
                    second->y = first->y + board->boardMatrix[i][j]->moves[currMove]->y;  
                    move->x = second->x - first->x;
                    move->y = second->y - second->y;  
                    if (moveIsValid(first, second, move, board, side, false)) //if there is at least one move that is valid return true
                    {
                        free(first);
                        free(second);
                        free(move);
                        return true;
                    }
                }
            }
        }
    }
    free(first);
    free(second);
    free(move);
    return false; //if not return false
}

/*
This fucntion is designed to check if any given move you make will put your own king in check.
The general idea of this function is as follows:
1. make the move
2. make sure there is no opposing piece that is now attacking your king
3. if there is undo the move
*/
bool moveCausesCheck(coordinate* first, coordinate* second, board* board, char currentSide, bool currentBeenMoved, bool keepMove)
{
    //assume all other checks have been made first, always put this last in checking order
    //make move
    int captureListLen = 56;
    coordinate* captureList[captureListLen];
    for (int i = 0; i < captureListLen; i++) {captureList[i] = buildCoordinate(0,0);}
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
                    captureList[0]->x = board->boardMatrix[i][j]->moves[2]->x;
                    captureList[0]->y = board->boardMatrix[i][j]->moves[2]->y;
                    captureList[1]->x = board->boardMatrix[i][j]->moves[3]->x;
                    captureList[1]->y = board->boardMatrix[i][j]->moves[3]->y;
                }
                else //every other piece can capture with any move
                {
                    for (int move = 0; move < board->boardMatrix[i][j]->movesLen; move++) 
                    {
                        captureList[move]->x = board->boardMatrix[i][j]->moves[move]->x;
                        captureList[move]->y = board->boardMatrix[i][j]->moves[move]->y;
                    }
                }
                //printf("i: %i j: %i\n", i, j);
                //loop through capture list and check if it has a move that could capture your king
                for (int move = 0; move < board->boardMatrix[i][j]->movesLen; move++)
                {
                    currMoveX = i + captureList[move]->x; //set hypothetical move relative to current piece position
                    currMoveY = j + captureList[move]->y;
                    //if current side's king is in check now, we need to undo the move and return true
                    //printf("Move: %i X: %i Y: %i\n", move, captureList[move]->x, captureList[move]->y);
                    if (currMoveX < 0 || currMoveX > 7 || currMoveY < 0 || currMoveY > 7) {continue;} //if move is out of range of board go to next loop iteration
                    if (board->boardMatrix[currMoveX][currMoveY]->display == 'k' && board->boardMatrix[currMoveX][currMoveY]->side == currentSide) 
                    {
                        makeMove(second, first, board, currentBeenMoved); //move whatever is at destination square back
                        buildPiece(board, secondDisplay, second->x, second->y, secondSide); //make copy of what used to be at second at second square again
                        board->boardMatrix[second->x][second->y]->hasBeenMoved = secondhasBeenMoved;
                        for (int space = 0; space < captureListLen; space++){free(captureList[space]);}
                        //printf("Move puts king in check\n");
                        return true;
                    }
                }
            }
            
        }
    }
    for (int space = 0; space < captureListLen; space++){free(captureList[space]);}
    //printf("Move does not put king in check\n");
    //printf("Keeping move? %i\n", keepMove);
    if (!keepMove) 
    {
        makeMove(second, first, board, currentBeenMoved); //move whatever is at destination square back
        buildPiece(board, secondDisplay, second->x, second->y, secondSide); //make copy of what used to be at second at second square again
    }
    else 
    {
        if (board->boardMatrix[second->x][second->y]->display == 'p')
            promotePawn(second, board);
    }
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
    while (true)
    {
        //get input from user
        char* intitialPrompt = "What would you like to do?\n1. Move\n2. View piece info\n3. Quit\n";
        printf("%s", intitialPrompt);
        scanf("%s", &input);

        if (input[0] == 'q' || input == "quit") { //allow user to quit by exiting main loop
            break;
        }
         
        if (!checkInputSyntax(input))
            continue;
        first->x = atoi(&input[1]) - 1; //reassign coordinat`es 
        first->y = atoi(&input[3]) - 1;
        second->x = atoi(&input[7]) - 1; //reassign coordinates
        second->y = atoi(&input[9]) - 1;
        bool canCastle = canPerformCastle(first, second, move, mainBoard);
        bool moveValid = moveIsValid(first, second, move, mainBoard, side, true);
        //we need to subtract one becasue we start counting at zero, but a human will start counting at one
        if (!moveValid && !canCastle)
            continue;
        else if (canCastle)
            performCastle(first, second, mainBoard);
        //not included in moveIsValid because we can't castle to get out of check
        
        //change side
        if (side == 'w')
            side = 'b';
        else
            side = 'w';

        bool inMove = sideCanMove(mainBoard, side);
        bool inCheck = sideInCheck(mainBoard, side);
        printBoard(mainBoard);

        if (!inMove && inCheck)
        {
            printf("Side: %c is in checkmate!\n", side);
            break;
        }
        else if (!inMove && !inCheck)
        {
            printf("Stalemate!\n");
            break;
        }
        else if (inCheck)
            printf("king in check!\n");
    }
    free(first);
    free(second);
    free(move);
}