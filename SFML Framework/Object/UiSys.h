#pragma once
#include "TileMap.h"

class UiSys : public GameObject
{
protected:
	TileMap timeBar;
	TileMap statusBar;
	
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
};
