#pragma once
#include "Scene.h"
#include "Card.h"

class Card;
class Deck;
class UiSys;

class GameScene : public Scene
{
public:
	enum class Status
	{
		Play,
		Pause,
		NextTurn,
		GameOver,
	};

protected:
	sf::Sprite background;

	sf::Vector2f viewPos;
	sf::FloatRect viewArea = { 1920 * 0.5f, 1080 * 0.5f, 1920 * 3.f, 1080 * 3.f};

	Card* card;
	Deck* deck;

	bool selectCard = false;
	bool selectDeck = false;

	std::list<Deck*> decks;
	ObjectPool<Deck> deckPool;

	std::list<Card*> cards;
	ObjectPool<Card> cardPool;

	UiSys* ui;
	int coinCnt;
	int needFood;
	int haveFood;
	int maxCardCnt;
	int cardCnt;

	bool pause;
	Status status;

public:

	GameObject* topGoWorld;
	GameObject* topGoUi;
	std::list<std::vector<Card*>> cardCombineList;

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
	void ZoomCard(Card* card);


	//void Collision(Card* card1, Card* card2);
	void Collision(Card* card, Deck* deck, float dt);

	void RemoveDeck(Deck* deck);
	void CreateDeck(int order);

	void ReturnCard(Card* card);
	Card* CreateCard(const std::string& id);

	int MaxCardOrder();
	
	void SetCombineList();
	
	void CheckCount();

	void SetStatus(Status st);

	void GiveFood();
};