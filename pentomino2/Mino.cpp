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

const int Mino::MINO_SIZE = 20;
const int Mino::MINO_NUM = 12;
const int Mino::MINO_CELLS = 5;

const int Mino::FRAME_THICKNESS = 1;

Mino::Mino(int ID0, Vec2 pos0) {
	ID = ID0;
	angle = 0;
	fixed = false;
	color = MINO_COLOR[ID];

	shape.resize(8, Array<Vector2D<int> >(MINO_CELLS));

	shape[0] = MINO_SHAPE[ID];
	/*for (int angle = 0; angle < 4 - 1; angle++) {
		for (int cell = 0; cell < MINO_CELLS; cell++) {
			shape[angle+1][cell].x = shape[angle][cell].y * -1;
			shape[angle + 1][cell].y = shape[angle][cell].x;
		}
	}
	for (int angle = 0; angle < 4; angle++) {
		for (int cell = 0; cell < MINO_CELLS; cell++) {
			shape[angle + 4][cell].x = shape[angle][cell].y;
			shape[angle + 4][cell].y = shape[angle][cell].x;
		}
	}*/
  for (int cell = 0; cell < MINO_CELLS; cell++) {
		// shape[0][cell] = { MINO_SHAPE[ID][cell].x, MINO_SHAPE[ID][cell].y };
		shape[1][cell] = { MINO_SHAPE[ID][cell].y * -1 ,MINO_SHAPE[ID][cell].x };
		shape[2][cell] = { MINO_SHAPE[ID][cell].x * -1,MINO_SHAPE[ID][cell].y * -1 };
		shape[3][cell] = { MINO_SHAPE[ID][cell].y, MINO_SHAPE[ID][cell].x * -1 };
		shape[4][cell] = { MINO_SHAPE[ID][cell].y, MINO_SHAPE[ID][cell].x };
		shape[5][cell] = { MINO_SHAPE[ID][cell].x * -1 ,MINO_SHAPE[ID][cell].y };
		shape[6][cell] = { MINO_SHAPE[ID][cell].y * -1,MINO_SHAPE[ID][cell].x * -1 };
		shape[7][cell] = { MINO_SHAPE[ID][cell].x, MINO_SHAPE[ID][cell].y * -1 };
	}

	int vlen = int(MINO_VERTEX[ID].size());
	Array<Vec2> v(vlen);
	for (int i = 0; i < vlen; i++) {
		v[i] = {MINO_VERTEX[ID][i].x * MINO_SIZE,MINO_VERTEX[ID][i].y * MINO_SIZE};
	}

	polygon = Polygon(v);

	center2corner = -polygon.centroid();
	center2pos = center2corner + Vec2{ MINO_SIZE / 2, MINO_SIZE / 2 };

	polygon.moveBy(pos0 - polygon.centroid());
}

void Mino::rotate(int n) {
	if (fixed) return;

	polygon.rotateAt(polygon.centroid(), n * 90_deg);

	angle = (angle / 4) * 4 + (angle + 1) % 4;
}

void Mino::flip() {
	if (fixed) return;

	Vec2 center = polygon.centroid();

  polygon.scaleAt(center, { -1, 1 });
  polygon.rotateAt(polygon.centroid(), -1 * 90_deg);

  // flipping also flips the direction of rotation
  // {0, 1, 2, 3} to {4, 7, 6, 5}
  angle = ((8 - 1 - angle) / 4) * 4 + (8 - angle) % 4;
}

int Mino::getID() const {
	return ID;
}

Vec2 Mino::getPos() const {
	if (angle / 4 == 0) {
		return polygon.centroid() + center2pos.rotated((angle % 4) * 90_deg);
	}
	else {
		return polygon.centroid() + center2pos.yx().rotated((angle % 4) * 90_deg);
	}
}

Vec2 Mino::getCenterPos() const {
	return polygon.centroid();
}

Vec2 Mino::getCornerPos() const {
	if (angle / 4 == 0) {
		return polygon.centroid() + center2corner.rotated((angle % 4) * 90_deg);
	}
	else {
		return polygon.centroid() + center2corner.yx().rotated((angle % 4) * 90_deg);
	}
}

Array<Vector2D<int> > Mino::getShape() const {
	return shape[angle];
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
	polygon.moveBy(delta);
}

void Mino::setPos(Vec2 pos0) {
	if (angle / 4 == 0) {
		polygon.moveBy(pos0 - polygon.centroid() - center2pos.rotated((angle % 4) * 90_deg));
	}
	else {
		polygon.moveBy(pos0 - polygon.centroid() - center2pos.yx().rotated((angle % 4) * 90_deg));
	}
}

void Mino::setCenterPos(Vec2 pos0) {
	polygon.moveBy(pos0 - polygon.centroid());
}

void Mino::setCornerPos(Vec2 pos0) {
	if (angle / 4 == 0) {
		polygon.moveBy(pos0 - polygon.centroid() - center2corner.rotated((angle % 4) * 90_deg));
	}
	else {
		polygon.moveBy(pos0 - polygon.centroid() - center2corner.yx().rotated((angle % 4) * 90_deg));
	}
};

void Mino::draw() const {
	polygon.draw(color);

	/*for (int a = 0; a < MINO_CELLS; a++) {
		Circle(getPos() + Vec2{ MINO_SIZE * shape[angle][a].x, MINO_SIZE * shape[angle][a].y }, 2).draw();
	}*/

	/*Circle(getPos(), 2).draw();
	Circle(getCenterPos(), 2).draw();
	Circle(getCornerPos(), 2).draw();*/
}

void Mino::drawFrame() const {
	polygon.drawFrame(FRAME_THICKNESS, FRAME_COLOR);
}

bool Mino::mouseOver() const {
	return polygon.mouseOver();
}
