#include "stdafx.h"
#include "Timer.h"

Timer::Timer(const std::string& name)
	: GameObject(name)
{
}

void Timer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	timer.setPosition(position);
	timeBar.setPosition(timer.getGlobalBounds().left + timer.getGlobalBounds().width - 5.5f, 
		timer.getGlobalBounds().top + 5.5f);
}

void Timer::SetRotation(float angle)
{
	rotation = angle;
	timer.setRotation(rotation);
}

void Timer::SetScale(const sf::Vector2f& s)
{
	scale = s;
	timer.setScale(scale);
}

void Timer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(timer, originPreset);
	}
}

void Timer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	timer.setOrigin(origin);
}

void Timer::Init()
{
	sortingLayer = SortingLayers::Card;
}

void Timer::Release()
{
}

void Timer::Reset()
{
}

void Timer::Update(float dt)
{
}

void Timer::Draw(sf::RenderWindow& window)
{
	window.draw(timer);
	window.draw(timeBar);
	
}

void Timer::SetType(Timer::Type t)
{
	switch (t)
	{
	case Timer::Type::TurnTimer:
		break;
	case Timer::Type::CombineTimer:
		timerTex = "graphics/icon/LoadBar2.png";
		SetComineTimer();
		break;
	default:
		break;
	}
}

void Timer::SetComineTimer()
{
	timer.setTexture(TEXTURE_MGR.Get(timerTex));
	timer.setScale(0.5f, 0.5f);
	SetOrigin(Origins::BC);

	timeBar.setSize({ 0.f ,timer.getGlobalBounds().height });
	Utils::SetOrigin(timeBar, Origins::TR);
}

void Timer::SetTimeBar(float time)
{
	float value = time / maxTime;
	sf::Vector2f maxSize = { -timer.getGlobalBounds().width + 11.f, timer.getGlobalBounds().height - 11.f };
	timeBar.setSize({ maxSize.x * value, maxSize.y });
}
