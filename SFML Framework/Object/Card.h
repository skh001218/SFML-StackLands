#pragma once

class Card : public GameObject
{
protected:
	sf::Sprite body;
	std::string bodyTexture = "graphics/card/yellowCard.png";

	sf::Sprite icon;
	std::string iconTex = "graphics/icon/Villager.png";
	sf::Text cardName;

	bool isSelect = false;


	//Villager
	std::string id;
	int health;
	float attackSpeed;
	float hitChance;
	int damage;
	int foodEat;

	sf::Sprite hpSprite;
	std::string hpTex = "";

public:
	Card(const std::string& name = "");
	~Card() = default;

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

	void SetSelectCard();
	bool GetSelectCard() const { return isSelect; };

	sf::Sprite GetCardBody() const { return body; }

	void CardSetting();
};

