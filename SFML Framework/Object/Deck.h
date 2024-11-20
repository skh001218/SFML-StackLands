#pragma once

class GameScene;

class Deck : public GameObject
{
protected:
	sf::Sprite body;
	std::string bodyTex = "graphics/deck/aNewWorld.png";

	std::list<std::string> deckList;

	sf::Text count;
	int deckCount;
	int deckOrder = 0;

	bool isSelect;
	sf::FloatRect movableArea = { 165, 290, 1580, 690 };

	GameScene* scene;

public:
	Deck(const std::string& name = "");
	~Deck() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const override { return body.getLocalBounds(); };
	sf::FloatRect GetGlobalBounds() const override { return body.getGlobalBounds(); };

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetSelectDeck();
	bool GetSelectDeck() const { return isSelect; };

	void SetDeckOrder(int order) { deckOrder = order; };
	int GetDeckOrder() const { return deckOrder; };

	sf::Sprite GetBody() const { return body; }

	void SettingDeck();

	void SetDeckList(int order);
	void ShowCard();
	void Move();

	void Collision();
};
