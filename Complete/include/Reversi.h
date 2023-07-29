#pragma once

typedef enum Stone
{
	Black,
	White,
	Empty,
	Placeable
} Stone;

typedef unsigned long long Board;

// 置いてある石の場所
Board BlackBoard, WhiteBoard;

// 置ける場所
Board BlackPlaceableBoard, WhitePlaceableBoard;

static Stone Turn;

int main();

int UpdateTurn(Stone *stone);