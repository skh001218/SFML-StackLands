#pragma once

class Card;

class Store : public GameObject
{
protected:
	std::string id;
	std::vector<sf::Sprite> stores;
	std::string storesTexture = "graphics/playArea/sellArea.png";

	std::vector<sf::Text> texts;

	Card* card;
	bool isCardCollision;

public:
	Store(const std::string& name = "");
	~Store() = default;

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

	void SettingStoreArea();
	void SellCard();
};
