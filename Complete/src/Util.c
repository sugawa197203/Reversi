#include "Util.h"

void XY2StonePos(int *x, int *y)
{
	*x = *x * 4 + 6;
	*y = *y * 2 + 3;
}

Board XY2Board(int x, int y)
{
	// 最上部 bit だけ立てる
	Board board = 0x8000000000000000;
	board >>= x;
	board >>= y * 8;
	return board;
}

int ConsolePos2XY(int *x, int *y)
{
	switch (*x)
	{
	case 5 ... 7:
		*x = 0;
		break;
	case 9 ... 11:
		*x = 1;
		break;
	case 13 ... 15:
		*x = 2;
		break;
	case 17 ... 19:
		*x = 3;
		break;
	case 21 ... 23:
		*x = 4;
		break;
	case 25 ... 27:
		*x = 5;
		break;
	case 29 ... 31:
		*x = 6;
		break;
	case 33 ... 35:
		*x = 7;
		break;
	default:
		return -1;
	}

	switch (*y)
	{
	case 3:
		*y = 0;
		break;
	case 5:
		*y = 1;
		break;
	case 7:
		*y = 2;
		break;
	case 9:
		*y = 3;
		break;
	case 11:
		*y = 4;
		break;
	case 13:
		*y = 5;
		break;
	case 15:
		*y = 6;
		break;
	case 17:
		*y = 7;
		break;
	default:
		return -1;
	}

	return 0;
}