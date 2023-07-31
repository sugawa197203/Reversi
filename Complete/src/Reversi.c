#include "Reversi.h"

void InitBoard();
Board CaluculatePlaceableBoard(Board checkBoard, Board opponent); // プロトタイプ宣言
void UpdatePlaceable();											  // プロトタイプ宣言
void UpdateScore();												  // プロトタイプ宣言
int IsPlaceable(int x, int y, Stone stone);						  // プロトタイプ宣言
Board BoardShift(Board board, Direction direction);				  // プロトタイプ宣言
int Place(int x, int y, Stone stone);							  // プロトタイプ宣言
Stone UpdateTurn(Stone stone);									  // プロトタイプ宣言
int IsGame();													  // プロトタイプ宣言

int main()
{
	int x, y;
	InitDisplay();

	InitBoard(); // 盤の初期化

	while (IsGame())
	{
		do
		{
			GetMousePos(&x, &y);
		} while (Place(x, y, Turn) != 0); // 置けるまでループ

		UpdatePlaceable();		 // 置ける場所の更新
		Turn = UpdateTurn(Turn); // ターンの更新
		PrintTurn(Turn);		 // ターンの表示

		PrintBlank();
		PrintBoard(BlackBoard, Black);
		PrintBoard(WhiteBoard, White);
		PrintBoard(Turn == Black ? BlackPlaceableBoard : WhitePlaceableBoard, Placeable); // 置ける場所の表示

		UpdateScore();						// スコアの更新
		PrintScore(BlackScore, WhiteScore); // スコアの表示
	}

	PrintResult(BlackScore, WhiteScore); // 結果の表示

	DisposeDisplay();
	return 0;
}

// 盤の初期化
// 石を初期配置にして表示
void InitBoard()
{
	BlackBoard = 0x0000000810000000;
	WhiteBoard = 0x0000001008000000;

	UpdatePlaceable();
	UpdateScore();

	PrintBlank();
	PrintBoard(BlackBoard, Black);
	PrintBoard(WhiteBoard, White);
	PrintBoard(BlackPlaceableBoard, Placeable); // はじめは黒がおける場所を表示

	PrintTurn(Turn);
	PrintScore(BlackScore, WhiteScore);
}

// おける場所の計算
Board CaluculatePlaceableBoard(Board checkBoard, Board opponent)
{
	// 左右のマスク
	Board horizon = opponent & 0x7e7e7e7e7e7e7e7eul;
	// 上下のマスク
	Board vertical = opponent & 0x00FFFFFFFFFFFF00ul;
	// 全辺のマスク
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

// 置ける場所の更新
void UpdatePlaceable()
{
	BlackPlaceableBoard = CaluculatePlaceableBoard(BlackBoard, WhiteBoard);
	WhitePlaceableBoard = CaluculatePlaceableBoard(WhiteBoard, BlackBoard);
}

// スコアの更新
void UpdateScore()
{
	BlackScore = __builtin_popcountll(BlackBoard);
	WhiteScore = __builtin_popcountll(WhiteBoard);
}

// 置けるかどうか判定
int IsPlaceable(int x, int y, Stone stone)
{
	// 盤をビットボードに変換
	Board pos = XY2Board(x, y);

	switch (stone)
	{
	case Black:
		return (BlackPlaceableBoard & pos) ? 1 : 0;
	case White:
		return (WhitePlaceableBoard & pos) ? 1 : 0;
	}
}

// borad 全体を指定した方向にずらす
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
	}
}

// 石を置く
int Place(int x, int y, Stone stone)
{
	if (!IsPlaceable(x, y, stone))
		return -1;

	Board placePos = XY2Board(x, y);							  // 置く場所
	Board *opponent = stone == Black ? &WhiteBoard : &BlackBoard; // 相手の石
	Board *me = stone == Black ? &BlackBoard : &WhiteBoard;		  // 自分の石
	Board reverse = 0ull;										  // ひっくり返す石

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

// ターンの更新
// パス判定もする
Stone UpdateTurn(Stone stone)
{
	if (stone == Black && __builtin_popcountll(WhitePlaceableBoard) > 0)
		return White;
	else if (stone == White && __builtin_popcountll(BlackPlaceableBoard) > 0)
		return Black;
	else
		return stone; // パス
}

// ゲームの終了判定
int IsGame()
{
	if (__builtin_popcountll(WhitePlaceableBoard) == 0 && __builtin_popcountll(BlackPlaceableBoard) == 0)
		return 0;
	return 1;
}