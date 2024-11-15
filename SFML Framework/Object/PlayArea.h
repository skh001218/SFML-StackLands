#pragma once
#include "Store.h"

class PlayArea : public GameObject
{
protected:
	sf::Sprite body;
	std::string bodyTexture = "graphics/playArea/board.png";

	Store* store;

	std::list<Card*> cards;
	ObjectPool<Card> cardPool;
public:
	PlayArea(const std::string& name = "");
	~PlayArea() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void CreateCard();
};



