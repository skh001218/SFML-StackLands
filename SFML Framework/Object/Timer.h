#pragma once

class Timer : public GameObject
{
public:
	enum class Type
	{
		TurnTimer,
		CombineTimer,
	};
protected:
	sf::Sprite timer;
	std::string timerTex = "graphics/icon/LoadBar.png";

	sf::RectangleShape timeBar;

	float maxTime;

public:
	Timer(const std::string& name = "");
	~Timer() = default;

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

	void SetMaxTime(float mt) { maxTime = mt; }
	float GetMaxTime() const { return maxTime; }

	void SetType(Timer::Type t);

	void SetComineTimer();

	void SetTimeBar(float time);
};
