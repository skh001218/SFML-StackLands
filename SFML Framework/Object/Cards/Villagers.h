#pragma once
class Villagers : public Card
{
private:

	std::string id;
	int health;
	float attackSpeed;
	float hitChance;
	int damage;
	int foodEat;

	sf::Sprite hpSprite;
	std::string hpTex = "";

public:
	Villagers() = default;
	virtual ~Villagers() = default;

	void Setting(std::string id);
};