#include "stdafx.h"
#include "Deck.h"
#include "GameScene.h"

Deck::Deck(const std::string& name)
	: GameObject(name)
{
}

void Deck::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
	count.setPosition({ position.x - 47.f, position.y - 71.f });
}

void Deck::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Deck::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Deck::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Deck::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Deck::Init()
{
	scene = dynamic_cast<GameScene*>(SCENE_MGR.GetCurrentScene());
}

void Deck::Release()
{
}

void Deck::Reset()
{
	scene = dynamic_cast<GameScene*>(SCENE_MGR.GetCurrentScene());
	SettingDeck();
}

void Deck::Update(float dt)
{
	SetSelectDeck(); Move();
	sf::Vector2f mousePos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(InputMgr::GetMousePosition());
	if (body.getGlobalBounds().contains(mousePos) && InputMgr::GetMouseButtonUp(sf::Mouse::Left) && !isSelect)
	{
		ShowCard();
		deckCount--;
		if (deckCount == 0)
		{
			SCENE_MGR.GetCurrentScene()->RemoveGo(this);
		}
	}
		
}

void Deck::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(count);
}

void Deck::SetSelectDeck()
{
	sf::Vector2f mousePos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(InputMgr::GetMousePosition());
	if (body.getGlobalBounds().contains(mousePos) && InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		isSelect = true;
	else if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
		isSelect = false;
}

void Deck::SettingDeck()
{
	body.setTexture(TEXTURE_MGR.Get(bodyTex));
	SetScale({0.15,0.15});
	SetOrigin(Origins::MC);

	count.setFont(FONT_MGR.Get("fonts/NotoSansKR-Medium.otf"));
	count.setString("5");
	count.setCharacterSize(100);
	count.setScale({0.15, 0.15});
	deckCount = 5;

	SetPosition(FRAMEWORK.GetWindowCenterPos());
}

void Deck::ShowCard()
{
	ObjectPool<Card>* cardPool = scene->GetObjectPool();
	std::list<Card*>* cards = scene->GetCardList();

	Card* card = cardPool->Take();
	cards->push_back(card);

	card->CardSetting();

	sf::Vector2f pos = Utils::RandomInUnitCircle() * 200.f;
	card->SetPosition(position + pos);

	scene->AddGo(card);
}

void Deck::Move()
{
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && isSelect)
	{
		sf::Vector2f mPos = scene->ScreenToWorld(InputMgr::GetMousePositionB()) - 
			scene->ScreenToWorld(InputMgr::GetMousePosition());
		SetPosition(position - mPos);
	}
}
