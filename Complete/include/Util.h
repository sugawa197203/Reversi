#pragma once

#include "Stone.h"

#define COUNT_STONE(board) __builtin_popcountll(board)

void XY2ConsolePos(int *x, int *y);
Board XY2Board(int x, int y);
int ConsolePos2XY(int *x, int *y);