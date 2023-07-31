#pragma once

#include "Display.h"
#include "Stone.h"

// 置いてある石の場所
Board BlackBoard, WhiteBoard;

// 置ける場所
Board BlackPlaceableBoard, WhitePlaceableBoard;

// スコア
int BlackScore, WhiteScore;

// ターン
Stone Turn = Black;