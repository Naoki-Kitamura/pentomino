#pragma once

#include "Board.hpp"
#include "Mino.hpp"

class Game : public SceneManager<String, String>::Scene
{
	Array<Mino> mino;
	Array<Point> minoInitialPos;
	Array<int> order;
	Board board;

	int remMinos;
	int grubbed;
	int selected;

	const Font font;

	static const int ROWS_CLASSIC = 6;
	static const int COLS_CLASSIC = 10;
	static const int ROWS_BLANK = 8;
	static const int COLS_BLANK = 8;
public:
	Game(const InitData& init);

	void update() override;
	void draw() const override;
};
