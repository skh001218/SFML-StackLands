#pragma once
class Villagers : public Card, public GameObject
{
private:

public:
	Villagers() = default;
	virtual ~Villagers() = default;

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

	void Setting(std::string id);
};