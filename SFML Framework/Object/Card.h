#pragma once

class GameScene;

class Card : public GameObject
{
protected:
	sf::Sprite body;

	sf::Sprite icon;
	sf::Text cardName;

	sf::Font font = FONT_MGR.Get("fonts/NotoSansKR-Medium.otf");

	std::string id;
	bool isSelect = false;

	GameScene* scene;

	sf::FloatRect movableArea = { 165, 290, 1745, 980 };

	bool isCombine = false;

	int health;
	float attackSpeed;
	float hitChance;
	int damage;
	int foodEat;
	int value;

	sf::Sprite hpSprite;
	std::string hpTex = "";
	sf::Text hpStr;

	sf::Text coinStr;

	Card* combineUp;
	Card* combineDown;
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
	void SetId(const std::string& id) { this->id = id; };
	std::string GetId() const { return id; };
	void SetValue(int val) { this->value = val; };
	int GetValue() const { return value; };

	void SetCombineUp(Card* card) { this->combineUp = card; };
	Card* GetCombineUp() const { return combineUp; };
	void SetCombineDown(Card* card) { this->combineDown = card; };
	Card* GetCombineDown() const { return combineDown; };

	sf::Sprite GetCardBody() const { return body; }

	void CardSetting(std::string id);
	void Move();
	void MoveInArea();

	void CombineCard();
};

