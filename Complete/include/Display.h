#pragma once

#include <ncurses.h>
#include "Stone.h"
#include "Util.h"

static const char Blank[] = "\
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
+---+---+---+---+---+---+---+---+---+";

void InitDisplay();
void PrintBlank();
void DisposeDisplay();
void PrintBoard(Board board, Stone stone);
void PrintScore(int black, int white);
void GetMousePos(int *x, int *y);
void PrintTurn(Stone stone);
void PrintResult(int black, int white);
