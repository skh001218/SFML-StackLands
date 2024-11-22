#include "stdafx.h"
#include "UiSys.h"

UiSys::UiSys(const std::string& name)
	: GameObject(name)
{
}

void UiSys::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiSys::SetRotation(float angle)
{
	rotation = angle;
}

void UiSys::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiSys::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiSys::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiSys::Init()
{
}

void UiSys::Release()
{
}

void UiSys::Reset()
{
	timeBar.Reset();
	timeBar.SetOrigin(Origins::TR);
	timeBar.SetPosition(FRAMEWORK.GetWindowCenterPos());
	timeBar.Set({ 4, 2 }, { 84.f, 84.f });
	timeBar.SetScale({ 1.f,0.3f });
}

void UiSys::Update(float dt)
{
}

void UiSys::Draw(sf::RenderWindow& window)
{
	timeBar.Draw(window);
}
