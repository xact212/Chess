#ifndef GAME_H
#define GAME_H
#include "board.h"
#include <stdbool.h>

void gameLoop(char startingSide, board* mainBoard);
bool checkInputSyntax(char* inputStr);
bool check(bool expression, char* successStr, char* failStr);
#endif