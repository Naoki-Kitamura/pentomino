#pragma once

class Title : public SceneManager<String>::Scene
{
public:
	Title(const InitData& init);

	void update() override;
	void draw() const override;
};
