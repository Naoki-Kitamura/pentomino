#pragma once
#include "Mino.hpp"

class Board {
	int rows, cols;
	Array<Array<int> > state;
	Point pos;

	Rect back;
	Array<LineString> line;

	static const int STATE_FREE;
	static const int STATE_BLANK;
public:
	static const Point BOARD_CENTER;
	static const Color BOARD_COLOR;
	static const Color BLANK_BOLOR;
	static const int GRID_THICKNESS;
	static const Color GRID_COLOR;

	// Board();
	Board(int rows_, int cols_);
	void resize(int rows0, int cols0);
	void draw() const;

	bool setBlank(int x, int y);
	bool setBlank(int x, int y, Mino* mino);

	bool setMino(Mino* mino);
	bool removeMino(Mino* mino);
};
