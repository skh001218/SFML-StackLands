#include "stdafx.h"
#include "PlayArea.h"

PlayArea::PlayArea(const std::string& name)
	: GameObject(name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void PlayArea::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void PlayArea::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void PlayArea::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(s);
}

void PlayArea::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void PlayArea::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void PlayArea::Init()
{
	
}

void PlayArea::Release()
{
}

void PlayArea::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(bodyTexture));
	body.setPosition(FRAMEWORK.GetWindowCenterPos());
	Utils::SetOrigin(body, Origins::MC);
	SettingStoreArea();
}

void PlayArea::Update(float dt)
{
}

void PlayArea::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	for (auto& store : stores)
		window.draw(store);
	for (auto& text : texts)
		window.draw(text);
}

void PlayArea::SettingStoreArea()
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
