#include "Board.h"
#include "Reversi.h"

void BoardInit()
{
	BlackBoard = 1ul << 28ul | 1ul << 35ul;
	WhiteBoard = 1ul << 27ul | 1ul << 36ul;
}

Board boardShift(Board board, Direction direction)
{
	switch (direction)
	{
	case 0: // 上
		return (board << 8) & 0xffffffffffffff00;
	case 1: // 右上
		return (board << 7) & 0x7f7f7f7f7f7f7f00;
	case 2: // 右
		return (board >> 1) & 0x7f7f7f7f7f7f7f7f;
	case 3: // 右下
		return (board >> 9) & 0x007f7f7f7f7f7f7f;
	case 4: // 下
		return (board >> 8) & 0x00ffffffffffffff;
	case 5: // 左下
		return (board >> 7) & 0x00fefefefefefefe;
	case 6: // 左
		return (board << 1) & 0xfefefefefefefefe;
	case 7: // 左上
		return (board << 9) & 0xfefefefefefefe00;
	default:
		return 0;
	}
}

void UpdatePlaceable()
{
	BlackPlaceableBoard = CaluculatePlaceableBoard(BlackBoard, WhiteBoard);
	WhitePlaceableBoard = CaluculatePlaceableBoard(WhiteBoard, BlackBoard);
}

int IsPlaceable(int x, int y, Stone stone)
{
	Board pos = XY2Board(x, y);

	switch (stone)
	{
	case Black:
		return (BlackPlaceableBoard & pos) ? 1 : 0;
	case White:
		return (WhitePlaceableBoard & pos) ? 1 : 0;
	default:
		return -1;
	}
}

/// @brief
/// @param x
/// @param y
/// @param stone
/// @return 置けないときは-1を返す。置けたときはひっくり返した石の数を返す。
int Place(int x, int y, Stone stone)
{
	if (!IsPlaceable(x, y, stone))
		return -1;

	Board placePos = XY2Board(x, y);
	Board *opponent = stone == Black ? &WhiteBoard : &BlackBoard;
	Board *me = stone == Black ? &BlackBoard : &WhiteBoard;
	Board reverse = 0ull;

	// 8方向
	for (int direction = 0; direction < 8; direction++)
	{
		Board tmp = 0ull;
		Board mask = boardShift(placePos, (Direction)direction);

		// 相手の石があったらtmpに追加
		while (mask != 0ull && ((mask & *opponent) != 0ull))
		{
			tmp |= mask;
			mask = boardShift(mask, (Direction)direction);
		}

		// 挟んでたらreverseに追加
		if ((mask & *me) != 0ull)
			reverse |= tmp;
	}

	// ひっくり返す
	*me ^= placePos | reverse;
	*opponent ^= reverse;

	return 0;
}

Board CaluculatePlaceableBoard(Board checkBoard, Board opponent)
{
	// 左右の番人
	Board horizon = opponent & 0x7e7e7e7e7e7e7e7eul;
	// 上下の番人
	Board vertical = opponent & 0x00FFFFFFFFFFFF00ul;
	// 全辺の番人
	Board allSide = opponent & 0x007e7e7e7e7e7e00ul;
	// 空いてる場所
	Board blank = ~(checkBoard | opponent);

	Board tmp;
	Board result;

	// 左
	tmp = horizon & (checkBoard << 1);
	tmp |= horizon & (tmp << 1);
	tmp |= horizon & (tmp << 1);
	tmp |= horizon & (tmp << 1);
	tmp |= horizon & (tmp << 1);
	tmp |= horizon & (tmp << 1);
	result = blank & (tmp << 1);

	// 右
	tmp = horizon & (checkBoard >> 1);
	tmp |= horizon & (tmp >> 1);
	tmp |= horizon & (tmp >> 1);
	tmp |= horizon & (tmp >> 1);
	tmp |= horizon & (tmp >> 1);
	tmp |= horizon & (tmp >> 1);
	result |= blank & (tmp >> 1);

	// 上
	tmp = vertical & (checkBoard << 8);
	tmp |= vertical & (tmp << 8);
	tmp |= vertical & (tmp << 8);
	tmp |= vertical & (tmp << 8);
	tmp |= vertical & (tmp << 8);
	tmp |= vertical & (tmp << 8);
	result |= blank & (tmp << 8);

	// 下
	tmp = vertical & (checkBoard >> 8);
	tmp |= vertical & (tmp >> 8);
	tmp |= vertical & (tmp >> 8);
	tmp |= vertical & (tmp >> 8);
	tmp |= vertical & (tmp >> 8);
	tmp |= vertical & (tmp >> 8);
	result |= blank & (tmp >> 8);

	// 右斜め上
	tmp = allSide & (checkBoard << 7);
	tmp |= allSide & (tmp << 7);
	tmp |= allSide & (tmp << 7);
	tmp |= allSide & (tmp << 7);
	tmp |= allSide & (tmp << 7);
	tmp |= allSide & (tmp << 7);
	result |= blank & (tmp << 7);

	// 左斜め上
	tmp = allSide & (checkBoard << 9);
	tmp |= allSide & (tmp << 9);
	tmp |= allSide & (tmp << 9);
	tmp |= allSide & (tmp << 9);
	tmp |= allSide & (tmp << 9);
	tmp |= allSide & (tmp << 9);
	result |= blank & (tmp << 9);

	// 右斜め下
	tmp = allSide & (checkBoard >> 9);
	tmp |= allSide & (tmp >> 9);
	tmp |= allSide & (tmp >> 9);
	tmp |= allSide & (tmp >> 9);
	tmp |= allSide & (tmp >> 9);
	tmp |= allSide & (tmp >> 9);
	result |= blank & (tmp >> 9);

	// 左斜め下
	tmp = allSide & (checkBoard >> 7);
	tmp |= allSide & (tmp >> 7);
	tmp |= allSide & (tmp >> 7);
	tmp |= allSide & (tmp >> 7);
	tmp |= allSide & (tmp >> 7);
	tmp |= allSide & (tmp >> 7);
	result |= blank & (tmp >> 7);

	return result;
}

int CountStone(Board board)
{
	Board bit = board - ((board >> 1) & 0x5555555555555555);
	bit = (bit & 0x3333333333333333) + ((bit >> 2) & 0x3333333333333333);
	bit = (bit + (bit >> 4) & 0x0f0f0f0f0f0f0f0f);
	bit = bit + (bit >> 8);
	bit = bit + (bit >> 16);
	bit = bit + (bit >> 32);
	return bit & 0x0000007f;
}