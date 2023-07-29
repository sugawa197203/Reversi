#include "Reversi.h"

int main()
{
	int x, y;
	InitDisplay();
	InitBoard();

	while (IsGame())
	{
		do
		{
			GetMousePos(&x, &y);
		} while (Place(x, y, Turn) != 0);

		UpdatePlaceable();
		UpdateScore();
		Turn = UpdateTurn(Turn);

		PrintTurn(Turn);
		PrintScore(BlackScore, WhiteScore);

		PrintBlank();
		PrintBoard(BlackBoard, Black);
		PrintBoard(WhiteBoard, White);
		PrintBoard(Turn == Black ? BlackPlaceableBoard : WhitePlaceableBoard, Placeable);
	}

	PrintResult(BlackScore, WhiteScore);

	DisposeDisplay();

	return 0;
}

int IsGame()
{
	if (COUNT_STONE(WhitePlaceableBoard) == 0 && COUNT_STONE(BlackPlaceableBoard) == 0)
		return 0;
	return 1;
}

Stone UpdateTurn(Stone stone)
{
	if (stone == Black && COUNT_STONE(WhitePlaceableBoard) > 0)
		return White;
	else if (stone == White && COUNT_STONE(BlackPlaceableBoard) > 0)
		return Black;
	else
		return stone;
}

void UpdateScore()
{
	BlackScore = COUNT_STONE(BlackBoard);
	WhiteScore = COUNT_STONE(WhiteBoard);
}

void InitBoard()
{
	BlackBoard = 0x0000000810000000;
	WhiteBoard = 0x0000001008000000;

	UpdatePlaceable();
	UpdateScore();

	PrintBlank();
	PrintBoard(BlackBoard, Black);
	PrintBoard(WhiteBoard, White);
	PrintBoard(Turn == Black ? BlackPlaceableBoard : WhitePlaceableBoard, Placeable);

	PrintTurn(Turn);
	PrintScore(BlackScore, WhiteScore);
}

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
		Board mask = BoardShift(placePos, (Direction)direction);

		// 相手の石があったらtmpに追加
		while (mask != 0ull && ((mask & *opponent) != 0ull))
		{
			tmp |= mask;
			mask = BoardShift(mask, (Direction)direction);
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

void UpdatePlaceable()
{
	BlackPlaceableBoard = CaluculatePlaceableBoard(BlackBoard, WhiteBoard);
	WhitePlaceableBoard = CaluculatePlaceableBoard(WhiteBoard, BlackBoard);
}

Board BoardShift(Board board, Direction direction)
{
	switch (direction)
	{
	case Up:
		return (board << 8) & 0xffffffffffffff00;
	case UpRight:
		return (board << 7) & 0x7f7f7f7f7f7f7f00;
	case Right:
		return (board >> 1) & 0x7f7f7f7f7f7f7f7f;
	case DownRight:
		return (board >> 9) & 0x007f7f7f7f7f7f7f;
	case Down:
		return (board >> 8) & 0x00ffffffffffffff;
	case DownLeft:
		return (board >> 7) & 0x00fefefefefefefe;
	case Left:
		return (board << 1) & 0xfefefefefefefefe;
	case UpLeft:
		return (board << 9) & 0xfefefefefefefe00;
	default:
		return 0;
	}
}
