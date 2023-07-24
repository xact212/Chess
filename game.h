#ifndef GAME_H
#define GAME_H
#include "board.h"
#include <stdbool.h>

void gameLoop(char startingSide, board* mainBoard);
bool checkInputSyntax(char* inputStr);
bool check(bool expression, char* successStr, char* failStr);
bool moveCausesCheck(coordinate* first, coordinate* second, board* board, char currentSide, bool currentBeenMoved, bool keepMove);
void makeMove(coordinate* first, coordinate* second, board* board, bool currentBeenMoved);
bool sideInCheck(board* board, char currentSide);
bool sideCanMove(board* board, char side);
bool moveIsValid(coordinate* first, coordinate* second, coordinate* move, board* board, char side, bool keepMove);
#endif