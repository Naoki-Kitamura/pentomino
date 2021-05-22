#pragma once
#include <Siv3D.hpp>
#include "Mino.hpp"

class Board {
	Array<Array<int> > state;
	Vec2 pos;
	Rect back;
	Array<LineString> line;

	Array<Vector2D<int> > shape[12];

public:
	static const int BOARD_ROW = 6;
	static const int BOARD_COLUMN = 10;
	static const Point BOARD_POS;
	static const Color BOARD_COLOR;
	static const int GRID_THICKNESS = 2;
	static const Color GRID_COLOR;

	Board();
	void draw();

	bool SetMino(Mino* mino);

	void removeMino(Mino* mino);
};
