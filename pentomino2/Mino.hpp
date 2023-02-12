#pragma once

class Mino {
	int ID;
	Array<Array<Vector2D<int> > > shape;
	Color color;

	Polygon polygon;
	Vec2 center2pos;
	Vec2 center2corner;

	int angle;

	bool fixed;

public:
	static const int MINO_SIZE;
	static const int MINO_NUM;
	static const int MINO_CELLS;
	
	static const int FRAME_THICKNESS;

	static const Array<Vector2D<int> > MINO_SHAPE[];
	static const Array<Vector2D<int> > MINO_VERTEX[];
	static const Color MINO_COLOR[];
	static const Color FRAME_COLOR;

	Mino(int ID0, Vec2 pos0);

	void rotate(int n);
	void flip();

	int getID() const;
	Vec2 getPos() const;
	Vec2 getCenterPos() const;
	Vec2 getCornerPos() const;
	Array<Vector2D<int> > getShape() const;
	bool isFixed() const;

	void fix();
	void unfix();
	void moveBy(Vec2 delta);
	void setPos(Vec2 pos0);
	void setCenterPos(Vec2 pos0);
	void setCornerPos(Vec2 pos0);

	void draw() const;
	void drawFrame() const;
	bool mouseOver() const;
};
