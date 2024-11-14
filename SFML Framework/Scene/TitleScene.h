#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
protected:
	sf::RectangleShape rect;
public:
	TitleScene();
	~TitleScene() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

