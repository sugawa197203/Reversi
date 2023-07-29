#pragma once

enum STONE
{
	Black,
	White,
	Empty,
	Placeable
};

typedef enum Direction
{
	Up,
	UpRight,
	Right,
	DownRight,
	Down,
	DownLeft,
	Left,
	UpLeft
} Direction;

typedef enum STONE Stone;
typedef unsigned long long Board;
