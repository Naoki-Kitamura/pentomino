#pragma once

#include "Board.hpp"

const Point Board::BOARD_POS = { 300,120 };
const Color Board::BOARD_COLOR = Palette::White;
const Color Board::GRID_COLOR = Palette::Gray;

Board::Board() {
	int i, j;
	state = Array<Array<int> >(BOARD_COLUMN, Array<int>(BOARD_ROW));
	pos = BOARD_POS;
	back = Rect(BOARD_POS, { Mino::MINO_SIZE * BOARD_COLUMN,Mino::MINO_SIZE * BOARD_ROW });
	for (i = 1; i < BOARD_COLUMN; i++) {
		line.push_back(LineString{ pos + Vec2(Mino::MINO_SIZE * i, 0), pos + Vec2(Mino::MINO_SIZE * i, Mino::MINO_SIZE * BOARD_ROW) });
	}
	for (i = 1; i < BOARD_ROW; i++) {
		line.push_back(LineString{ pos + Vec2(0,Mino::MINO_SIZE * i), pos + Vec2(Mino::MINO_SIZE * BOARD_COLUMN,Mino::MINO_SIZE * i) });
	}

	for (i = 0; i < BOARD_COLUMN; i++) {
		for (j = 0; j < BOARD_ROW; j++) {
			state[i][j] = -1;
		}
	}
}

void Board::draw(){
	back.draw(BOARD_COLOR);
	for (int i = 0; i < BOARD_ROW + BOARD_COLUMN - 2; i++) {
		line[i].draw(GRID_THICKNESS, GRID_COLOR);
	}
	back.drawFrame(GRID_THICKNESS, GRID_COLOR);
}

bool Board::SetMino(Mino* mino) {
	Vec2 rpos = mino->getPos() - Vec2{ BOARD_POS } -Vec2{ Mino::MINO_SIZE / 2,Mino::MINO_SIZE / 2 };
	int x = int(round(rpos.x / Mino::MINO_SIZE));
	int y = int(round(rpos.y / Mino::MINO_SIZE));
	int i;

	int ID = mino->getID();

	if (x >= 0 && x < BOARD_COLUMN && y >= 0 && y < BOARD_ROW) {
		shape[ID] = mino->getRotatedShape();
		for (i = 0; i < Mino::MINO_BLOCKS; i++) {
			shape[ID][i] += {x, y};
			if (shape[ID][i].x >= 0 && shape[ID][i].x < BOARD_COLUMN && shape[ID][i].y >= 0 && shape[ID][i].y < BOARD_ROW && state[shape[ID][i].x][shape[ID][i].y] < 0) {
				continue;
			}
			else {
				return false;
			}
		}

		for (i = 0; i < Mino::MINO_BLOCKS; i++) {
			state[shape[ID][i].x][shape[ID][i].y] = ID;
		}
		mino->setPos(Vec2{ BOARD_POS }+Vec2{ x * Mino::MINO_SIZE,y * Mino::MINO_SIZE } +Vec2{ Mino::MINO_SIZE / 2,Mino::MINO_SIZE / 2 });
		mino->fix();
		return true;
	}
	else {
		return false;
	}
}

void Board::removeMino(Mino* mino) {
	if (mino->isFixed()) {
		int ID = mino->getID();
		int i;

		for (i = 0; i < 5; i++) {
			state[shape[ID][i].x][shape[ID][i].y] = -1;
		}

		mino->unfix();
	}
}
