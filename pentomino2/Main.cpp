#include "stdafx.h"
#include "Title.hpp"
#include "Game.hpp"

void Main()
{
	Window::SetTitle(U"Pentomino(alpha)");
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	SceneManager<String> manager;

	manager.add<Title>(U"Title");
	manager.add<Game>(U"Game");

	while (System::Update())
	{
		if (!manager.update()) {
			break;
		}
	}
}
