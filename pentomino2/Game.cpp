#include "stdafx.h"
#include "Game.hpp"

Game::Game(const InitData& init)
	: IScene{ init }, board(Board(6, 10)), font(Font{ 30 }) {

	// board.resize(6, 10);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			minoInitialPos.push_back({ 60 + 120 * j ,360 + 120 * i });
			mino.push_back(Mino(i * 6 + j, minoInitialPos[i * 6 + j]));
			order.push_back(i * 6 + j);
		}
	}

	remMinos = 12;
	grubbed = -1;
	selected = -1;
}

void Game::update() {
	if (remMinos == 0) {
		font(U"Clear!").draw(0, 0, Palette::Black);
		if (SimpleGUI::Button(U"Quit", Vec2{ 360, 360 }))
		{
			changeScene(U"Title");
		}

		if (SimpleGUI::Button(U"Restart", Vec2{ 360, 420 }))
		{
			changeScene(U"Game");
		}
	}

	if (grubbed >= 0) {
		selected = grubbed;
		mino[grubbed].moveBy(Cursor::Delta());

		if (MouseL.up()) {
			if (board.setMino(&mino[grubbed])) {
				remMinos--;
			}
			else {
				auto pos = mino[grubbed].getPos();
				if (pos.x < 0 || pos.x > Scene::Size().x || pos.y < 0 || pos.y > Scene::Size().y) {
					mino[grubbed].setPos(minoInitialPos[grubbed]);
				}
			}			

			grubbed = -1;
		}
		else if (MouseL.pressed()) {
			if (MouseR.up()) mino[grubbed].rotate(1);
			if (MouseM.up()) mino[grubbed].flip();
		}
	}
	else {
		if (Cursor::Delta() != Point(0, 0)) {
			selected = -1;
		}
		for (int i = Mino::MINO_NUM - 1; i >= 0; i--) {
			if (mino[order[i]].mouseOver()) {
				selected = order[i];

				break;
			}
		}

		if (selected == -1) return;

		if (MouseL.down()) {
			grubbed = selected;

			if (board.removeMino(&mino[grubbed])) {
				remMinos++;
			}

			order.remove(selected);
			order.push_back(selected);
		}
		else {
			if (MouseR.up()) {
				mino[selected].rotate(1);
				order.remove(selected);
				order.push_back(selected);
			}
			if (MouseM.up()) {
				mino[selected].flip();
				order.remove(selected);
				order.push_back(selected);
			}
		}
	}
}

void Game::draw() const {
	board.draw();
	for (int i = 0; i < Mino::MINO_NUM; i++) {
		mino[order[i]].draw();
	}
	if (selected >= 0) mino[selected].drawFrame();
}
