#ifndef GAME_H
#define GAME_H
#include "board.h"
#include <stdbool.h>

void gameLoop(char startingSide, board* mainBoard);
bool checkInputSyntax(char* inputStr);
bool check(bool expression, char* successStr, char* failStr);
bool moveCausesCheck(coordinate* first, coordinate* second, board* board, char currentSide, bool currentBeenMoved);
void makeMove(coordinate* first, coordinate* second, board* board, bool currentBeenMoved);
#endif