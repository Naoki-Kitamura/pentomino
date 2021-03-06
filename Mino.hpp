#pragma once

#include <Siv3D.hpp>


class Mino {
	int ID;
	Vec2 pos;

	Array<Vector2D<int>> shape;
	Color color;

	Polygon polygon;
	int angle;
	bool flipped;

	bool fixed;

public:
	static const int MINO_SIZE = 20;
	static const int MINO_NUM = 12;
	static const int MINO_BLOCKS = 5;
	
	static const int FRAME_THICKNESS = 1;

	static const Array<Vector2D<int> > MINO_SHAPE[];
	static const Array<Vector2D<int> > MINO_VERTEX[];
	static const Color MINO_COLOR[];
	static const Color FRAME_COLOR;

	Mino(int ID0, Vec2 pos0);

	void rotate(int n);
	void flip();

	void setPos(Vec2 newPos);	int getID();
	Vec2 getPos();
	Array<Vector2D<int> > getRotatedShape();

	bool isFixed();
	void fix();
	void unfix();
	void moveBy(Vec2 delta);
	void draw();
	void drawFrame();
	bool mouseOver();
};