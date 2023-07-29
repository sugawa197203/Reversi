#pragma once

#include "Stone.h"
#include "Display.h"

// 置いてある石の場所
Board BlackBoard, WhiteBoard;
// 置ける場所
Board BlackPlaceableBoard, WhitePlaceableBoard;
// ターン(今置く石の色)
Stone Turn = Black;
// スコア
int BlackScore, WhiteScore;

int main();
Stone UpdateTurn(Stone stone);

void InitBoard();
int IsGame();
int Place(int x, int y, Stone stone);
int IsPlaceable(int x, int y, Stone stone);
Board CaluculatePlaceableBoard(Board checkBoard, Board opponent);
void UpdatePlaceable();
void UpdateScore();
Board BoardShift(Board board, Direction direction);
