#pragma once
#include "Scene.h"
#include "UiSys.h"

class TileMap;

class TitleScene : public Scene
{
protected:
	sf::Sprite background; 

	TileMap* menu;
	UiSys* temp;
	sf::Sprite menuLine;
	std::vector<sf::Text> menuStr;

	std::vector<sf::RectangleShape> backStr;
	std::vector<sf::RectangleShape> lines;

	bool isChange;
	std::vector<sf::RectangleShape> next;
public:
	TitleScene();
	~TitleScene() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetMenu();
	void SetBackMenuStr();
	void DoAction(int i);
	void ChangeScene(float dt);
};

