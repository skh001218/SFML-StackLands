#include "stdafx.h"
#include "Card.h"

Card::Card(const std::string& name)
	: GameObject(name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 3;
}

void Card::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
	icon.setPosition(position);
	cardName.setPosition(body.getGlobalBounds().left + body.getGlobalBounds().width - 12.f,
		body.getGlobalBounds().top + body.getGlobalBounds().height - 14.f);
	//cardName.setPosition(body.getGlobalBounds().left + 5.f, body.getGlobalBounds().top + 3.f);
	hpSprite.setPosition(body.getGlobalBounds().left + body.getGlobalBounds().width - 5.f, 
		body.getGlobalBounds().top + body.getGlobalBounds().height - 3.f);
}

void Card::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Card::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Card::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Card::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Card::Init()
{
}

void Card::Release()
{
}

void Card::Reset()
{
	
	CardSetting();
	
}

void Card::Update(float dt)
{
	SetSelectCard();
	hitbox.UpdateTr(body, body.getLocalBounds());
}

void Card::FixedUpdate(float dt)
{

}

void Card::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	
	window.draw(icon);
	window.draw(hpSprite);
	window.draw(cardName);
	hitbox.Draw(window);
}

void Card::SetSelectCard()
{
	sf::Vector2f mousePos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(InputMgr::GetMousePosition());
	if (body.getGlobalBounds().contains(mousePos) && InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		isSelect = true;
	else if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
		isSelect = false;
}

void Card::CardSetting()
{
	this->id = "Villager";
	body.setTexture(TEXTURE_MGR.Get(bodyTexture));
	SetOrigin(Origins::MC);
	body.setScale(0.22f, 0.22f);

	iconTex = VILLAGER_TABLE->Get(this->id).iconTex;
	icon.setTexture(TEXTURE_MGR.Get(iconTex));
	Utils::SetOrigin(icon, Origins::MC);
	icon.setScale(0.05f, 0.05f);

	cardName.setFont(FONT_MGR.Get("fonts/NotoSansKR-Medium.otf"));
	//cardName.setString(VILLAGER_TABLE->Get(this->id).name);
	cardName.setString("15");
	cardName.setCharacterSize(150);
	//cardName.setScale(0.1f, 0.1f);
	cardName.setScale(0.07f, 0.07f);
	cardName.setFillColor(sf::Color::White);
	Utils::SetOrigin(cardName, Origins::BR);

	hitbox = HitBox();

	
	health = VILLAGER_TABLE->Get(this->id).health;
	attackSpeed = VILLAGER_TABLE->Get(this->id).attackSpeed;
	hitChance = VILLAGER_TABLE->Get(this->id).hitChance;
	damage = VILLAGER_TABLE->Get(this->id).damage;
	foodEat = VILLAGER_TABLE->Get(this->id).foodEat;
	hpSprite.setTexture(TEXTURE_MGR.Get("graphics/icon/Ui_Hart.png"));
	hpSprite.setColor(sf::Color::Black);
	hpSprite.setScale(0.05f, 0.05f);
	Utils::SetOrigin(hpSprite, Origins::BR);
	
	SetPosition(FRAMEWORK.GetWindowCenterPos());
}