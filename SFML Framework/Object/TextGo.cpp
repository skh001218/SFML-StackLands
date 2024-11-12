#include "stdafx.h"
#include "TextGo.h"

TextGo::TextGo(const std::string& fontId, const std::string& name)
	: GameObject(name), fontId(fontId)
{
}

void TextGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(text, originPreset);
}

void TextGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	text.setOrigin(origin);
}

void TextGo::Reset()
{
	text.setFont(FONT_MGR.Get(fontId));
	SetString(stringId);
	SetOrigin(originPreset);
}

void TextGo::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	text.setPosition(pos);
}

void TextGo::SetRotation(float angle)
{
	rotation = angle;
	text.setRotation(angle);
}

void TextGo::SetScale(const sf::Vector2f& s)
{
	scale = s;
	text.setScale(scale);
}

void TextGo::Draw(sf::RenderWindow& window)
{
	if(active)
		window.draw(text);
}

void TextGo::OnLocalize(Languages lang)
{
	text.setString(STRING_TABLE->Get(stringId, lang));
	SetOrigin(originPreset);
}

void TextGo::Set(int size, const sf::Color &color)
{
	text.setCharacterSize(size);
	text.setFillColor(color);
}

void TextGo::SetString(const std::string& id)
{
	std::string temp;
	stringId = id;
	text.setString(STRING_TABLE->Get(stringId));
	std::cout << temp.assign(STRING_TABLE->Get(stringId).begin(), STRING_TABLE->Get(stringId).end());
	SetOrigin(originPreset);

	//text.setString(id);
}

void TextGo::SetString(const std::wstring& str)
{
	text.setString(str);
}

void TextGo::Init()
{
}

void TextGo::Release()
{
}

void TextGo::Update(float dt)
{
}
