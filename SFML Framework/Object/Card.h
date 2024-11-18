#pragma once

class GameScene;

class Card : public GameObject
{
protected:
	sf::Sprite body;
	std::string bodyTexture = "graphics/card/yellowCard.png";

	sf::Sprite icon;
	std::string iconTex = "graphics/icon/Villager.png";
	sf::Text cardName;

	sf::Font font = FONT_MGR.Get("fonts/NotoSansKR-Medium.otf");

	bool isSelect = false;

	GameScene* scene;

	sf::FloatRect movableArea = { 165, 290, 1745, 980 };

	bool isCombine = false;

	//Villager
	std::string id;
	int health;
	float attackSpeed;
	float hitChance;
	int damage;
	int foodEat;

	sf::Sprite hpSprite;
	std::string hpTex = "";
	sf::Text hpStr;

public:
	Card(const std::string& name = "");
	~Card() = default;

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

	void SetSelectCard();
	bool GetSelectCard() const { return isSelect; };

	sf::Sprite GetCardBody() const { return body; }

	void CardSetting();
	void Move();
	void MoveInArea();

	void CombineCard();
};

