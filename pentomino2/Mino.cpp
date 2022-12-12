#include "stdafx.h"
#include "Mino.hpp"

const Array<Vector2D<int> > Mino::MINO_SHAPE[] = {
			{{0,0},{1,0},{2,0},{3,0},{4,0}},
			{{0,0},{1,0},{2,0},{3,0},{0,1}},
			{{0,0},{1,0},{2,0},{3,0},{1,1}},
			{{0,0},{1,0},{2,0},{0,1},{1,1}},
			{{0,0},{1,0},{2,0},{0,1},{2,1}},
			{{0,0},{1,0},{2,0},{1,1},{1,2}},
			{{0,0},{1,0},{2,0},{0,1},{0,2}},
			{{0,0},{0,1},{1,1},{2,1},{2,2}},
			{{0,1},{1,0},{1,1},{1,2},{2,1}},
			{{0,0},{0,1},{1,1},{2,1},{1,2}},
			{{0,0},{1,0},{2,0},{2,1},{3,1}},
			{{0,0},{1,0},{1,1},{2,1},{2,2}}
};

const Array<Vector2D<int> > Mino::MINO_VERTEX[] = {
		{{0,0},{5,0},{5,1},{0,1}},
		{{0,0},{4,0},{4,1},{1,1},{1,2},{0,2}},
		{{0,0},{4,0},{4,1},{2,1},{2,2},{1,2},{1,1},{0,1}},
		{{0,0},{3,0},{3,1},{2,1},{2,2},{0,2}},
		{{0,0},{3,0},{3,2},{2,2},{2,1},{1,1},{1,2},{0,2}},
		{{0,0},{3,0},{3,1},{2,1},{2,3},{1,3},{1,1},{0,1}},
		{{0,0},{3,0},{3,1},{1,1},{1,3},{0,3}},
		{{0,0},{1,0},{1,1},{3,1},{3,3},{2,3},{2,2},{0,2}},
		{{1,0},{2,0},{2,1},{3,1},{3,2},{2,2},{2,3},{1,3},{1,2},{0,2},{0,1},{1,1}},
		{{0,0},{1,0},{1,1},{3,1},{3,2},{2,2},{2,3},{1,3},{1,2},{0,2}},
		{{0,0},{3,0},{3,1},{4,1},{4,2},{2,2},{2,1},{0,1}},
		{{0,0},{2,0},{2,1},{3,1},{3,3},{2,3},{2,2},{1,2},{1,1},{0,1}}
};

const Color Mino::MINO_COLOR[] = {
		Palette::Red,
		Palette::Blue,
		Palette::Green,
		Palette::Gold,
		Palette::Hotpink,
		Palette::Lightcoral,
		Palette::Teal,
		Palette::Limegreen,
		Palette::Purple,
		Palette::Dodgerblue,
		Palette::Orange,
		Palette::Sienna
};

const Color Mino::FRAME_COLOR = Palette::Black;

Mino::Mino(int ID0, Vec2 pos0) {
	ID = ID0;
	pos = pos0 + Vec2{ MINO_SIZE / 2, MINO_SIZE / 2 };

	shape = MINO_SHAPE[ID];

	Array<Vec2> v(MINO_VERTEX[ID].size());
	
	for (int i = 0; i < MINO_VERTEX[ID].size(); i++) {
		v[i] = { MINO_VERTEX[ID][i].x * MINO_SIZE,MINO_VERTEX[ID][i].y * MINO_SIZE };
	}

	polygon = Polygon(v).moveBy(pos0);
	angle = 0;
	flipped = 0;

	fixed = 0;

	color = MINO_COLOR[ID];
}

void Mino::rotate(int n) {
	if (fixed) return;

	angle = (angle + n) % 4;
	Vec2 v = pos - polygon.centroid();

	polygon.rotateAt(polygon.centroid(), n * 90_deg);

	pos = polygon.centroid() + v.rotated(n * 90_deg);
}

void Mino::flip() {
	if (fixed) return;

	flipped = !flipped;

	Vec2 prevCenter = polygon.centroid();

	int i;
	for (i = 0; i < MINO_BLOCKS; i++) {
		std::swap(shape[i].x, shape[i].y);
	}

  int vlen = MINO_VERTEX[ID].size();
	Array<Vec2> v(vlen);
	if (flipped) {
		for (i = 0; i < vlen; i++) {
			v[i] = { MINO_VERTEX[ID][vlen - i - 1].y * MINO_SIZE,MINO_VERTEX[ID][vlen - i - 1].x * MINO_SIZE };
		}
	}
	else {
		for (i = 0; i < MINO_VERTEX[ID].size(); i++) {
			v[i] = { MINO_VERTEX[ID][i].x * MINO_SIZE,MINO_VERTEX[ID][i].y * MINO_SIZE };
		}
	}

	polygon = Polygon(v).moveBy(pos - Vec2{ MINO_SIZE / 2,MINO_SIZE / 2 });

	Vec2 newCenter = polygon.centroid();

	int tmp = angle;
	angle = 0;
	rotate(tmp);

	moveBy(prevCenter - newCenter);
}

void Mino::setPos(Vec2 newPos) {
	polygon.moveBy(newPos - pos);
	pos = newPos;
}

int Mino::getID() const {
	return ID;
}

Vec2 Mino::getPos() const {
	return pos;
}

Array<Vector2D<int> > Mino::getRotatedShape() const {
	Array<Vector2D<int> > ret(MINO_BLOCKS);
	int i;

	if (angle == 0) {
		ret = shape;
	}
	else if (angle == 1) {
		for (i = 0; i < MINO_BLOCKS; i++) {
			ret[i] = { shape[i].y * -1 ,shape[i].x };
		}
	}
	else if (angle == 2) {
		for (i = 0; i < MINO_BLOCKS; i++) {
			ret[i] = { shape[i].x * -1,shape[i].y * -1 };
		}
	}
	else if (angle == 3) {
		for (i = 0; i < MINO_BLOCKS; i++) {
			ret[i] = { shape[i].y, shape[i].x * -1 };
		}
	}

	return ret;
}

bool Mino::isFixed() const {
	return fixed;
}

void Mino::fix() {
	fixed = true;
}

void Mino::unfix() {
	fixed = false;
}

void Mino::moveBy(Vec2 delta) {
	pos = pos + delta;
	polygon.moveBy(delta);
}

void Mino::draw() const {
	polygon.draw(color);

	//Circle(pos, 2).draw();
}

void Mino::drawFrame() const {
	polygon.drawFrame(FRAME_THICKNESS, FRAME_COLOR);
}

bool Mino::mouseOver() const {
	return polygon.mouseOver();
}
