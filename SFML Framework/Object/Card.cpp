#include "stdafx.h"
#include "Card.h"
#include "GameScene.h"

Card::Card(const std::string& name)
	: GameObject(name)
{
	sortingLayer = SortingLayers::Card;
}

void Card::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
	icon.setPosition(position);
	hpStr.setPosition(body.getGlobalBounds().left + body.getGlobalBounds().width - 12.f,
		body.getGlobalBounds().top + body.getGlobalBounds().height - 14.f);
	cardName.setPosition(body.getGlobalBounds().left + 5.f, body.getGlobalBounds().top + 3.f);
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
	scene = dynamic_cast<GameScene*>(SCENE_MGR.GetCurrentScene());
	CardSetting();
	
}

void Card::Update(float dt)
{
	SetSelectCard();
}

void Card::FixedUpdate(float dt)
{
	Move();
	MoveInArea();
}

void Card::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	
	window.draw(icon);
	window.draw(hpSprite);
	window.draw(cardName);
	window.draw(hpStr);
	hitbox.Draw(window);
}

void Card::SetSelectCard()
{
	sf::Vector2f mousePos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(InputMgr::GetMousePosition());
	std::list<Card*>* cards = scene->GetCardList();
	if (body.getGlobalBounds().contains(mousePos) && InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		cards->sort();
			
		isSelect = true;
	}
		
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

	cardName.setFont(font);
	cardName.setString(VILLAGER_TABLE->Get(this->id).name);
	cardName.setCharacterSize(150);
	cardName.setScale(0.1f, 0.1f);
	cardName.setFillColor(sf::Color::Black);

	hpStr.setFont(font);
	hpStr.setString("15");
	hpStr.setCharacterSize(150);
	hpStr.setScale(0.07f, 0.07f);
	hpStr.setFillColor(sf::Color::White);
	Utils::SetOrigin(hpStr, Origins::BR);
	
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

void Card::Move()
{
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && isSelect)
	{
		sf::Vector2f mPos = scene->ScreenToWorld(InputMgr::GetMousePositionB()) -
			scene->ScreenToWorld(InputMgr::GetMousePosition());
		SetPosition(position - mPos);
	}
}

void Card::MoveInArea()
{
	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
		if (GetGlobalBounds().top < movableArea.top)
		{
			position.y -= GetGlobalBounds().top - movableArea.top;
			SetPosition(position);
		}
		if (GetGlobalBounds().left < movableArea.left)
		{
			position.x -= GetGlobalBounds().left - movableArea.left;
			SetPosition(position);
		}
		if (GetGlobalBounds().top + GetGlobalBounds().height > movableArea.height)
		{
			position.y -= GetGlobalBounds().top + GetGlobalBounds().height - movableArea.height;
			SetPosition(position);
		}
		if (GetGlobalBounds().left + GetGlobalBounds().width > movableArea.width)
		{
			position.x -= GetGlobalBounds().left + GetGlobalBounds().width - movableArea.width;
			SetPosition(position);
		}
	}
}

void Card::CombineCard()
{
	std::list<Card*>* cards = scene->GetCardList();
	for (auto& card : *cards)
	{
		if (Utils::CheckCollision(body, card->GetCardBody()))
		{
			card->GetGlobalBounds().top - 10.f;
		}
	}
}
