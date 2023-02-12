#include "stdafx.h"
#include "Board.hpp"

const int Board::STATE_FREE = -1;
const int Board::STATE_BLANK = -2;

const Point Board::BOARD_CENTER = { 400,200 };
const Color Board::BOARD_COLOR = Palette::White;
const Color Board::BLANK_BOLOR = Palette::Darkgray;
const int Board::GRID_THICKNESS = 2;
const Color Board::GRID_COLOR = Palette::Gray;

// Board::Board(){}

Board::Board(int rows0, int cols0) {
	resize(rows0, cols0);
}

void Board::resize(int rows0, int cols0){
	int i, j;
	rows = rows0, cols = cols0;
	state = Array<Array<int> >(cols, Array<int>(rows));
	pos = BOARD_CENTER - Point(Mino::MINO_SIZE * cols / 2, Mino::MINO_SIZE * rows / 2);
	back = Rect(pos, { Mino::MINO_SIZE * cols,Mino::MINO_SIZE * rows });
	for (i = 1; i < cols; i++) {
		line.push_back(LineString{ pos + Vec2(Mino::MINO_SIZE * i, 0), pos + Vec2(Mino::MINO_SIZE * i, Mino::MINO_SIZE * rows) });
	}
	for (i = 1; i < rows; i++) {
		line.push_back(LineString{ pos + Vec2(0,Mino::MINO_SIZE * i), pos + Vec2(Mino::MINO_SIZE * cols,Mino::MINO_SIZE * i) });
	}

	for (i = 0; i < cols; i++) {
		for (j = 0; j < rows; j++) {
			state[i][j] = STATE_FREE;
		}
	}
}

void Board::draw() const {
	back.draw(BOARD_COLOR);
	for (int i = 0; i < rows + cols - 2; i++) {
		line[i].draw(GRID_THICKNESS, GRID_COLOR);
	}
	back.drawFrame(GRID_THICKNESS, GRID_COLOR);
}

bool Board::setBlank(int x, int y) {

	if (state[x][y] != STATE_FREE) {
		return false;
	}
	state[x][y] = STATE_BLANK;
	return true;
}

bool Board::setBlank(int x, int y, Mino* mino) {
	auto shape = mino->getShape();

	for (int i = 0; i < Mino::MINO_CELLS; i++) {
		if (setBlank(x + shape[i].x, y + shape[i].y)) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

bool Board::setMino(Mino* mino) {
	Vec2 mpos = mino->getPos() - Vec2{ pos };
	int x = int(floor(mpos.x / Mino::MINO_SIZE));
	int y = int(floor(mpos.y / Mino::MINO_SIZE));
	int i;

	int ID = mino->getID();
	Array<Vector2D<int> > shape = mino->getShape();

	for (i = 0; i < Mino::MINO_CELLS; i++) {
		if (x + shape[i].x >= 0 && x + shape[i].x < cols && y + shape[i].y >= 0 && y + shape[i].y < rows && state[x + shape[i].x][y + shape[i].y] == STATE_FREE) {
	    // Print << x + shape[i].x << U" " << y + shape[i].y;
			continue;
		}
		else {
			return false;
		}
	}

	for (i = 0; i < Mino::MINO_CELLS; i++) {
		state[x + shape[i].x][y + shape[i].y] = ID;
	}
	mino->setPos(Vec2{ pos } + Vec2{ (x+0.5) * Mino::MINO_SIZE, (y+0.5) * Mino::MINO_SIZE });
	mino->fix();
	return true;
}

bool Board::removeMino(Mino* mino) {
	if (mino->isFixed()) {
		Vec2 mpos = mino->getPos() - Vec2{ pos };
		int x = int(floor(mpos.x / Mino::MINO_SIZE));
		int y = int(floor(mpos.y / Mino::MINO_SIZE));
		Array<Vector2D<int> > shape = mino->getShape();

		for (int i = 0; i < Mino::MINO_CELLS; i++) {
			state[x + shape[i].x][y + shape[i].y] = STATE_FREE;
		}

		mino->unfix();
		return true;
	}

	return false;
}
