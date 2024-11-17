#include "stdafx.h"
#include "Store.h"
#include "Card.h"
#include "GameScene.h"

Store::Store(const std::string& name)
	: GameObject(name)
{
}

void Store::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	for (auto& store : stores)
		store.setPosition(position);
}

void Store::SetRotation(float angle)
{
	rotation = angle;
	for (auto& store : stores)
		store.setRotation(rotation);
}

void Store::SetScale(const sf::Vector2f& s)
{
	scale = s;
	for (auto& store : stores)
		store.setScale(scale);
}

void Store::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		for (auto& store : stores)
			origin = Utils::SetOrigin(store, originPreset);
	}
}

void Store::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	for (auto& store : stores)
		store.setOrigin(origin);
}

void Store::Init()
{
	
}

void Store::Release()
{
}

void Store::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 2;
	SettingStoreArea();
}

void Store::Update(float dt)
{
}

void Store::FixedUpdate(float dt)
{
	GameScene* scene = dynamic_cast<GameScene*>(SCENE_MGR.GetCurrentScene());
	if(scene->GetSelectCard() != nullptr)
		SellCard(scene->GetSelectCard());
}

void Store::Draw(sf::RenderWindow& window)
{
	for (auto& store : stores)
		window.draw(store);
	for (auto& text : texts)
		window.draw(text);
}

void Store::SettingStoreArea()
{
	for (int i = 0; i < 9; i++)
	{
		std::string id = "Buy" + std::to_string(i);
		stores.push_back(sf::Sprite());
		stores[i].setTexture(TEXTURE_MGR.Get(STORE_TABLE->Get(id).texture));
		stores[i].setScale({ 0.3f, 0.3f });
		stores[i].setPosition(STORE_TABLE->Get(id).pos);
		Utils::SetOrigin(stores[i], Origins::MC);

		texts.push_back(sf::Text());
		texts[i].setFont(FONT_MGR.Get(STORE_TABLE->Get(id).font));
		texts[i].setCharacterSize(20.f);
		texts[i].setString(STORE_TABLE->Get(id).stringNone);
		Utils::SetOrigin(texts[i], STORE_TABLE->Get(id).origin);
		texts[i].setPosition(STORE_TABLE->Get(id).posStr);

	}
}

void Store::SellCard(Card* card)
{
	if (Utils::PointInTransformBounds(stores[0], stores[0].getLocalBounds(), card->GetPosition()))
	{
		if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
		{
			card->SetActive(false);
		}
	}
}
