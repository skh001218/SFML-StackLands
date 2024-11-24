#pragma once
#include "TileMap.h"

class UiSys : public GameObject
{
protected:
	TileMap timeBar;
	sf::Text month;
	int months = 1;

	bool startMonth;
	float curTime;
	sf::RectangleShape time;

	sf::Sprite playBtn;
	std::vector<std::string> images = { "graphics/icon/play.png", "graphics/icon/fastforward.png",
		"graphics/icon/pause.png" };
	int curImage = 0;

	TileMap statusBar;

	sf::Text food;
	sf::Sprite foodSp;
	int needFood;
	int haveFood;
	
	sf::Text coin;
	sf::Sprite coinSp;
	int haveCoin;

	sf::Text card;
	sf::Sprite cardSp;
	int maxCard;
	int haveCard;

	TileMap progressBar;
	sf::Text text1;
	sf::Text text2;
	bool isProgress = false;
	bool isEnd = false;

	sf::Text menuStr;
	sf::RectangleShape backStr;
	sf::RectangleShape lines;

	float foodEatTime = 0;
	float dieTime = 0;
	float completeTime = 0;

	int curProgress = 0;

	GameScene* scene;
	
public:
	UiSys(const std::string& name = "");
	~UiSys() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetTimeBar();
	void SetMonth(int month);

	void SetStatus();
	void SetFood(int foods1, int foods2);
	void SetCoin(int coins);
	void SetCardCnt(int cards1, int cards2);

	void SetIsProgress(bool tf) { isProgress = tf; };
	bool GetIsProgress() const { return isProgress; }

	void NextTrun();
	void InputMsg();
	void SetProgressBar();
	void SetEndProgress();
};
