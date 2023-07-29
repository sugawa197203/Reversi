#include "Printer.c"
#include "Util.c"
#include "Board.c"

int main()
{
	int x, y;
	Turn = White; // 先手は黒だけど、UpdateTurnで黒になる

	InitDisplay();
	BoardInit();
	loop
	{
		UpdatePlaceable();
		if (UpdateTurn(&Turn))
			break;
		PrintBoard(Turn);
		PrintTurn(Turn);
		PrintScore();

		do
		{
			GetMousePos(&x, &y);
		} while (Place(x, y, Turn));
	}
	PrintBoard(Turn);
	PrintScore();
	PrintResult();
	PrinterDispose();
	return 0;
}

int UpdateTurn(Stone *stone)
{
	if (*stone == Black && COUNT_STONE(WhitePlaceableBoard) > 0)
	{
		*stone = White;
	}
	else if (*stone == White && COUNT_STONE(BlackPlaceableBoard) > 0)
	{
		*stone = Black;
	}
	else
	{
		// ゲームの終了
		*stone = Empty;
		return -1;
	}

	return 0;
}
