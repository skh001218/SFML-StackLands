#pragma once
#include "Scene.h"

class Card;

class GameScene : public Scene
{
protected:
	sf::Sprite background;

	sf::Vector2f viewPos;
	sf::FloatRect viewArea = { 1920 * 0.5f, 1080 * 0.5f, 1920 * 3.f, 1080 * 3.f};

	Card* card;
	bool selectCard = false;

public:
	GameScene();
	~GameScene() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void CloseUpDown(float dt);
	void MoveScreen(float dt);
	void MoveCard(Card* card);
};