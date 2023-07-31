#pragma once

enum STONE
{
	Black,
	White,
	Placeable
};

enum DIRECTION
{
	Up,
	UpRight,
	Right,
	DownRight,
	Down,
	DownLeft,
	Left,
	UpLeft
};

typedef enum DIRECTION Direction;

typedef enum STONE Stone;
typedef unsigned long long Board;
