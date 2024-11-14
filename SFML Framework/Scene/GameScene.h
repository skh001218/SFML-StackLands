#pragma once
#include "Scene.h"

class GameScene : public Scene
{
protected:
	sf::Sprite background;

	sf::Vector2f viewPos;
	sf::FloatRect viewArea = { 1920 * 0.5f, 1080 * 0.5f, 1920 * 2.f, 1080 * 2.f};

public:
	GameScene();
	~GameScene() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void CloseUpDown(float dt);
	void MoveScreen(float dt);
};