#include "coordinate.h"
#include "board.h"
#include "game.h"
#include "pawn.h"
#include "openSpace.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

pawn* buildPawn(char side)
{
    pawn* myPawn = malloc(sizeof(pawn) * 2);
    myPawn->display = 'p';
    myPawn->side = side;
    myPawn->hasBeenMoved = false;
    myPawn->movesLen = 4;
    coordinate** moves = malloc(myPawn->movesLen * sizeof(coordinate*));
    if (side == 'w')
    {
        moves[0] = buildCoordinate(0,2); //   0
        moves[1] = buildCoordinate(0,1); // 2 1 3
        moves[2] = buildCoordinate(-1,1);//  wp
        moves[3] = buildCoordinate(1,1);
    }
    else if (side == 'b')
    {
        moves[0] = buildCoordinate(0,-2); //  bp
        moves[1] = buildCoordinate(0,-1); // 2 1 3
        moves[2] = buildCoordinate(-1,-1);//   0
        moves[3] = buildCoordinate(1,-1);
    }
    myPawn->moves = moves; //can move up one or two, depends on hasBeenmoved variable for move 2
    return myPawn;
}

void promotePawn(coordinate* currentPos, board* board)
{//assume we already checked if pawn 
    bool isWhiteAtTop = (board->boardMatrix[currentPos->x][currentPos->y]->side == 'w' && currentPos->y == 7);
    bool isBlackAtBottom = (board->boardMatrix[currentPos->x][currentPos->y]->side == 'b' && currentPos->y == 0);
    if (isWhiteAtTop || isBlackAtBottom)
    {
        bool inputValid = false;
        while(!inputValid)
        {
            //prompt user to change piece
            char input[1024];
            puts("You have a pawn ready to promote!\nWhich piece would you like to choose?");
            puts("q = queen\nr = rook\nK = knight\nb = bishop");
            scanf("%s", &input);

            if (input[0] != 'q' && input[0] != 'r' && input[0] != 'K' && input[0] != 'b')
            {
                puts("Invalid character, please try again");
                continue;
            }
            printf("input: %c\n", input[0]);
            inputValid = true;
            buildPiece(board, input[0], currentPos->x, currentPos->y, board->boardMatrix[currentPos->x][currentPos->y]->side);
        }
        
    }
}

bool checkPawn(coordinate* first, coordinate* second, coordinate* move, board* board) 
{
    if ((board->boardMatrix[first->x][first->y]->hasBeenMoved && (move->y == 2 || move->y == -2))) //if has been moved and is trying to move 2 spaces
    {
        return false;
    }
    else
    {
        board->boardMatrix[first->x][first->y]->hasBeenMoved = true; //if hasn't made move before, set it so the pawn cant make it again
    }    
    //capturing
    //code to move a piece should also work for captures, unless piece is a pawn or king
    //if piece we are moving into is not an open space, and we are using our non capture moves, move is invalid
    if (move->x == 0 && board->boardMatrix[second->x][second->y]->side != 'n')
    {
        //puts("Trying to capture with non-capture move");
        return false;
    }
    if ((move->x == 1 || move->x == -1) && board->boardMatrix[second->x][second->y]->moves[0] == NULL)
    {
        //puts("Trying to capture open space");
        return false;
    }
    return true;
}