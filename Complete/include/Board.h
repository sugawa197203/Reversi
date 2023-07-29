#pragma once

#include "Reversi.h"

typedef enum Direction
{
	Up = 0,
	UpperRight = 1,
	Right = 2,
	LowerRight = 3,
	Under = 4,
	LowerLeft = 5,
	Left = 6,
	UpperLeft = 7
} Direction;

void BoardInit();
int Place(int x, int y, Stone stone);
int IsPlaceable(int x, int y, Stone stone);
Board CaluculatePlaceableBoard(Board checkBoard, Board opponent);
void UpdatePlaceable();
Board BoardShift(Board board, Direction direction);
