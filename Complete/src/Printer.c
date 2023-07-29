#include <ncurses.h>
#include <stdio.h>

#include "Printer.h"
#include "Util.h"

void InitDisplay()
{
	initscr();						   // ncursesの初期化
	noecho();						   // 入力された文字を表示しない
	curs_set(0);					   // カーソルを非表示
	keypad(stdscr, TRUE);			   // xtermでマウスイベントの取得に必要
	mousemask(ALL_MOUSE_EVENTS, NULL); // マウスイベントを取得

	start_color();
	init_pair(1, COLOR_GREEN, COLOR_GREEN); // 背景用の緑
	init_pair(2, COLOR_BLACK, COLOR_GREEN); // 緑背景黒文字
	init_pair(3, COLOR_WHITE, COLOR_GREEN); // 緑背景白文字
	init_pair(4, COLOR_CYAN, COLOR_GREEN);	// 置ける場所用
	init_pair(5, COLOR_WHITE, COLOR_BLACK); // 黒背景白文字
	init_pair(6, COLOR_BLACK, COLOR_WHITE); // 白背景黒文字
	init_pair(7, COLOR_BLACK, COLOR_BLACK);
	init_pair(8, COLOR_WHITE, COLOR_WHITE);
}

void PrintBoard(Stone placeabletarget)
{
	Board placeable = STONE2PLACEABLE(placeabletarget);
	Board pos;

	PrintBrank();

	for (Board i = 0; i < 8; i++)
	{
		for (Board j = 0; j < 8; j++)
		{
			pos = XY2Board(j, i);

			if (BlackBoard & pos)
			{
				PrintStone(j, i, Black);
			}
			else if (WhiteBoard & pos)
			{
				PrintStone(j, i, White);
			}
			else if (placeable & pos)
			{
				PrintStone(j, i, Placeable);
			}
		}
	}

	refresh();
}

void PrinterDispose()
{
	int ch;
	while ((ch = getch()) != 'q')
		;
	endwin();
}

void PrintStone(int x, int y, Stone stone)
{
	XY2StonePos(&x, &y);
	switch (stone)
	{
	case Black:
		SET_BLACK();
		mvaddstr(y, x, " ");
		break;
	case White:
		SET_WHITE();
		mvaddstr(y, x, " ");
		break;
	case Placeable:
		SET_CYAN_CHAR();
		mvaddstr(y, x, "*");
		break;
	default:
		break;
	}
}

void PrintBrank()
{
	SET_BLACK_CHAR();
	mvaddstr(0, 0, BLANK_BOARD);
}

void PrintTurn(Stone stone)
{
	SET_WHITE_BLACK();
	if (stone == Black)
		mvaddstr(20, 0, "Turn: Black");
	else
		mvaddstr(20, 0, "Turn: White");
}

void PrintScore()
{
	SET_WHITE_BLACK();
	mvprintw(22, 0, "Black: %d", COUNT_STONE(BlackBoard));
	mvprintw(23, 0, "White: %d", COUNT_STONE(WhiteBoard));
}

void GetMousePos(int *x, int *y)
{
	MEVENT event;
	int ch;

	loop
	{
		ch = getch();

		if (ch != KEY_MOUSE)
		{
			continue;
		}

		if (getmouse(&event) != OK)
		{
			continue;
		}

		*x = event.x;
		*y = event.y;

		// -1 が来たらだめ
		if (ConsolePos2XY(x, y))
			continue;

		break;
	}
}

void PrintResult()
{
	SET_WHITE_BLACK();
	if (COUNT_STONE(BlackBoard) > COUNT_STONE(WhiteBoard))
	{
		mvaddstr(25, 0, "Black Win!");
	}
	else if (COUNT_STONE(BlackBoard) < COUNT_STONE(WhiteBoard))
	{
		mvaddstr(25, 0, "White Win!");
	}
	else
	{
		mvaddstr(25, 0, "Draw!");
	}
}