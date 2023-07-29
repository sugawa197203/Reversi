#pragma once

#include <ncurses.h>
#include "Stone.h"
#include "Util.h"

#define SET_BLACK_CHAR() attrset(COLOR_PAIR(1))
#define SET_PLACEABLE() attrset(COLOR_PAIR(2))
#define SET_WHITE_BLACK() attrset(COLOR_PAIR(3))
#define SET_BLACK() attrset(COLOR_PAIR(4))
#define SET_WHITE() attrset(COLOR_PAIR(5))

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
void PrintBoard(Board board, Stone stone);
void PrintStone(int x, int y, Stone stone);
void PrintBlank();
void PrintTurn(Stone stone);
void PrintScore(int black, int white);
void DisposeDisplay();

void GetMousePos(int *x, int *y);
void PrintResult(int black, int white);