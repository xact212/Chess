#include "game.h"
#include "board.h"
#include "coordinate.h"
#include <stdlib.h>
#include <stdio.h>

void gameLoop(char startingSide, board* mainBoard)
{
    char side = startingSide;
    char input[999] = "0000000000"; //reason for large number is to prevent buffer overflow
    coordinate* first;
    coordinate* second;
    //while (1)
    //{
        //get input from user
        printf("Which move would you like to make? (Format: 1st coordinate [space] 2nd coordinate)\n");
        printf("Example to move pawn from 1st coordinate to 2nd coordinate: (3,3) (3,4)\n");
        printf("Will reprompt if: A: you try to move a piece that isn't yours B: you try to make "
        "an illegal move C: you try to put a coordinate that isn'n on the board\n");
        scanf("%s", &input);
        //check if valid
        //expecting coordinates to be from 1-8 rather than 0-7. this helps us because
        //atoi returns 0 if input is not integer
        printf("%s\n", input);
        printf("%i\n", atoi(&input[1]));
        if (input[0] == '(' && (atoi(&input[1]) > 0 && atoi(&input[1]) < 9)  && input[2] == ',' && 
        (atoi(&input[3]) > 0 && atoi(&input[3]) < 9) && input[4] == ')')
        {
            printf("first coordinate good\n");
        }
        else
        {
            printf("first coordinate bad, please re-enter move\n");
        }
        if (input[5] == '_' && input[6] == '(' && (atoi(&input[7]) > 0 && atoi(&input[7]) < 9)  && input[8] == ',' && 
        (atoi(&input[9]) > 0 && atoi(&input[9]) < 9) && input[10] == ')')
        {
            printf("second coordinate good\n");
        }
        else
        {
            printf("second coordinate bad, please re-enter move\n");
        }
    //}
    
}