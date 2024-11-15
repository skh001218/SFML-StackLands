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
	store = new Store();
}

void PlayArea::Release()
{
}

void PlayArea::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	body.setTexture(TEXTURE_MGR.Get(bodyTexture));
	SetPosition(FRAMEWORK.GetWindowCenterPos());
	//SetScale({ 2.f, 2.f });
	Utils::SetOrigin(body, Origins::MC);
	store->Reset();
}

void PlayArea::Update(float dt)
{
	
}

void PlayArea::FixedUpdate(float dt)
{
	store->FixedUpdate(dt);
}

void PlayArea::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	store->Draw(window);
}

void PlayArea::CreateCard()
{
	
}
