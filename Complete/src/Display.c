#include "Display.h"

void InitDisplay()
{
	initscr();						   // ncursesの初期化
	noecho();						   // 入力された文字を表示しない
	curs_set(0);					   // カーソルを非表示
	keypad(stdscr, TRUE);			   // マウスイベントの取得に必要
	mousemask(ALL_MOUSE_EVENTS, NULL); // マウスイベントを取得

	start_color();
	init_pair(1, COLOR_BLACK, COLOR_GREEN); // 盤面用
	init_pair(2, COLOR_BLACK, COLOR_BLACK); // 黒石用
	init_pair(3, COLOR_WHITE, COLOR_WHITE); // 白石用
	init_pair(4, COLOR_CYAN, COLOR_GREEN);	// 置ける場所用
	init_pair(5, COLOR_WHITE, COLOR_BLACK); // 情報表示用
}

// 石が置かれていない盤を表示
void PrintBlank()
{
	attrset(COLOR_PAIR(1));
	mvprintw(0, 0, Blank);
}

// 終了処理
void DisposeDisplay()
{
	while (getch() != 'q')
		;
	endwin();
}

// 盤の x, y に stone を表示
// stone が Placeable なら 置ける場所を表示
void PrintStone(int x, int y, Stone stone)
{
	XY2ConsolePos(&x, &y);

	switch (stone)
	{
	case Black:
		attrset(COLOR_PAIR(2));
		mvprintw(y, x, " ");
		break;
	case White:
		attrset(COLOR_PAIR(3));
		mvprintw(y, x, " ");
		break;
	case Placeable:
		attrset(COLOR_PAIR(4));
		mvprintw(y, x, "*");
		break;
	}
}

// board を stone として表示
// stone が Placeable なら 置ける場所を表示
void PrintBoard(Board board, Stone stone)
{
	Board pos;

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			pos = XY2Board(x, y);
			if (board & pos)
			{
				PrintStone(x, y, stone);
			}
		}
	}
}

// スコアを表示
void PrintScore(int black, int white)
{
	attrset(COLOR_PAIR(5));
	mvprintw(22, 0, "Black: %d", black);
	mvprintw(23, 0, "White: %d", white);
}

// マウスがクリックしたコンソールの座標を取得
// 盤の石を置ける場所をクリックするまで繰り返す
void GetMousePos(int *x, int *y)
{
	MEVENT event;
	int ch;

	do
	{
		ch = getch();

		// マウスのクリックか判定 (キーボードの可能性がある)
		if (ch != KEY_MOUSE)
		{
			continue;
		}

		// マウスのイベントを取得
		if (getmouse(&event) != OK)
		{
			continue;
		}

		// マウスのイベントからコンソールのどこをクリックしたかを取得
		*x = event.x;
		*y = event.y;

		// 盤の石を置ける場所をクリックしたか判定
	} while (ConsolePos2XY(x, y));
}

// ターンの情報を表示
void PrintTurn(Stone stone)
{
	attrset(COLOR_PAIR(5));
	switch (stone)
	{
	case Black:
		mvprintw(20, 0, "Turn: Black");
		break;
	case White:
		mvprintw(20, 0, "Turn: White");
		break;
	}
}

// 結果の表示
void PrintResult(int black, int white)
{
	attrset(COLOR_PAIR(5));
	if (black > white)
		mvprintw(20, 0, "Black Win! ");
	else if (black < white)
		mvprintw(20, 0, "White Win! ");
	else
		mvprintw(20, 0, "Draw!      ");

	mvprintw(25, 0, "Push Q Key...");
}
