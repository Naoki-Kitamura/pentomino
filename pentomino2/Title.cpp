#include "stdafx.h"
#include "Title.hpp"

Title::Title(const InitData& init)
	: IScene{ init } {

}

void Title::update() {
	if (SimpleGUI::Button(U"Classic", Vec2{ 100, 100 }))
	{
	  getData() = U"Classic";
		changeScene(U"Game");
	}
}

void Title::draw() const {

}
