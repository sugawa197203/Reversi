#pragma once

#include "Reversi.h"
#include "Util.h"

#define BLANK_BOARD "\
+---+---+---+---+---+---+---+---+---+\n\
|   | A | B | C | D | E | F | G | H |\n\
+---+---+---+---+---+---+---+---+---+\n\
| 1 |   |   |   |   |   |   |   |   |\n\
+---+---+---+---+---+---+---+---+---+\n\
| 2 |   |   |   |   |   |   |   |   |\n\
+---+---+---+---+---+---+---+---+---+\n\
| 3 |   |   |   |   |   |   |   |   |\n\
+---+---+---+---+---+---+---+---+---+\n\
| 4 |   |   |   |   |   |   |   |   |\n\
+---+---+---+---+---+---+---+---+---+\n\
| 5 |   |   |   |   |   |   |   |   |\n\
+---+---+---+---+---+---+---+---+---+\n\
| 6 |   |   |   |   |   |   |   |   |\n\
+---+---+---+---+---+---+---+---+---+\n\
| 7 |   |   |   |   |   |   |   |   |\n\
+---+---+---+---+---+---+---+---+---+\n\
| 8 |   |   |   |   |   |   |   |   |\n\
+---+---+---+---+---+---+---+---+---+"

void PrinterInit();
void PrintBoard(Stone placeabletarget);
void PrintStone(int x, int y, Stone stone);
void PrintBrank();
void PrintTurn(Stone stone);
void PrintScore();
void PrinterDispose();

void GetMousePos(int *x, int *y);
void PrintResult();