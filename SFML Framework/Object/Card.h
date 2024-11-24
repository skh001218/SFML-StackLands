#pragma once

class GameScene;

class Card : public GameObject
{
protected:
	sf::Sprite body;

	sf::Sprite icon;
	sf::Text cardName;

	std::map<std::string, int> table;

	sf::Font font = FONT_MGR.Get("fonts/NotoSansKR-Medium.otf");

	std::string id;
	bool isSelect = false;

	GameScene* scene;

	sf::FloatRect movableArea = { 165, 290, 1745, 980 };

	bool isCombine = false;
	bool StartCombine = false;

	bool isDie;
	int health;
	float attackSpeed;
	float hitChance;
	int damage;
	int foodEat;
	int foodGet;
	int value;
	int durability = 3;

	std::string resultId;
	float combineTime;
	float timer;

	sf::Sprite hpSprite;
	sf::Text hpStr;

	sf::Sprite coin;
	sf::Text coinStr;

	sf::Sprite foodSprite;
	sf::Text foodStr;

	Card* combineUp;
	Card* combineDown;

	sf::Vector2f topCardPos;
	Timer timeBar;
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
	bool GetIsSelect() const override { return isSelect; };
	void SetId(const std::string& id) { this->id = id; };
	std::string GetId() const { return id; };
	void SetValue(int val) { this->value = val; };
	int GetValue() const { return value; };

	void SetDurability(int du) { this->durability = du; };
	int GetDurability() const { return durability; };

	void SetCombineUp(Card* card) { this->combineUp = card; };
	Card* GetCombineUp() const { return combineUp; };
	void SetCombineDown(Card* card) { this->combineDown = card; };
	Card* GetCombineDown() const { return combineDown; };

	void SetFoodEat(int fe) { this->foodEat = fe; };
	int GetFoodEat() const { return foodEat; };

	void SetFoodGet(int fg) 
	{ 
		this->foodGet = fg; 
		foodStr.setString(std::to_wstring(foodGet));
	
	};
	int GetFoodGet() const { return foodGet; };

	sf::Sprite GetCardBody() const { return body; }

	void CardSetting(std::string id);
	void Move(float dt);
	void MoveInArea();

	void CombineCard();
	void SetCombineList();
	void CheckCombine();
	void CombineAction(float dt);

	void GetIsCombine();

	void IsDead();
	void EatFood(Card* card);
};

