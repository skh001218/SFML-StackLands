#pragma once
#include "Scene.h"
#include "Card.h"

class Card;
class Deck;

class GameScene : public Scene
{
protected:
	sf::Sprite background;

	sf::Vector2f viewPos;
	sf::FloatRect viewArea = { 1920 * 0.5f, 1080 * 0.5f, 1920 * 3.f, 1080 * 3.f};

	Card* card;
	Deck* deck;

	bool selectCard = false;
	bool selectDeck = false;

	std::list<Card*> cards;
	ObjectPool<Card> cardPool;

public:
	GameScene();
	~GameScene() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetSelectCard();
	Card* GetSelectCard() const { return card; }

	ObjectPool<Card>* GetObjectPool() { return &cardPool; };
	std::list<Card*>* GetCardList() { return &cards; };

	void CloseUpDown(float dt);
	void MoveScreen(float dt);

	//void Collision(Card* card1, Card* card2);
	void Collision(Card* card, Deck* deck, float dt);


	void CrateCard();
};