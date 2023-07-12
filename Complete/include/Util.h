#define loop while (1)
#define SET_GREEN_BACK() attrset(COLOR_PAIR(1))
#define SET_BLACK_CHAR() attrset(COLOR_PAIR(2))
#define SET_WHITE_CHAR() attrset(COLOR_PAIR(3))
#define SET_CYAN_CHAR() attrset(COLOR_PAIR(4))
#define SET_WHITE_BLACK() attrset(COLOR_PAIR(5))
#define SET_BLACK_WHITE() attrset(COLOR_PAIR(6))
#define SET_BLACK() attrset(COLOR_PAIR(7))
#define SET_WHITE() attrset(COLOR_PAIR(8))

#define STONE2BORAD(stone) (stone == Black ? BlackBoard : WhiteBoard)
#define STONE2PLACEABLE(stone) (stone == Black ? BlackPlaceableBoard : WhitePlaceableBoard)
#define COUNT_STONE(boad) __builtin_popcountll(boad)

void XY2StonePos(int *x, int *y);
Board XY2Board(int x, int y);
int ConsolePos2XY(int *x, int *y);