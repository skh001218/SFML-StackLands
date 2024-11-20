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
	count.setPosition({ body.getGlobalBounds().left + 11.f, body.getGlobalBounds().top + 5.f});
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
	sortingLayer = SortingLayers::Card;
	scene = dynamic_cast<GameScene*>(SCENE_MGR.GetCurrentScene());
	//SetDeckList(5, 0);
	SetDeckList(deckOrder);
	SettingDeck();
	
}

void Deck::Update(float dt)
{
	SetSelectDeck(); 
	Move();
	sf::Vector2f mousePos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(InputMgr::GetMousePosition());
	if (body.getGlobalBounds().contains(mousePos) && !InputMgr::GetMouseButton(sf::Mouse::Left) && 
		InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
		ShowCard();
		if (deckCount == 0)
		{
			scene->RemoveGo(this);
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
	if (body.getGlobalBounds().contains(mousePos) && InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		sortingOrder = scene->MaxCardOrder() + 1;
		isSelect = true;
	}
	else if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
		isSelect = false;
}

void Deck::SettingDeck()
{
	body.setTexture(TEXTURE_MGR.Get(DECK_TABLE->Get("DECK").texture));
	SetScale({0.15,0.15});
	SetOrigin(Origins::TC);

	count.setFont(FONT_MGR.Get("fonts/NotoSansKR-Medium.otf"));
	count.setString(std::to_string(DECK_TABLE->Get("DECK").count));
	count.setCharacterSize(100);
	count.setScale({0.15, 0.15});
	deckCount = DECK_TABLE->Get("DECK").count;

	if (deckOrder == 0)
		SetPosition(FRAMEWORK.GetWindowCenterPos());
	else
		SetPosition({ STORE_TABLE->Get("Buy" + std::to_string(deckOrder)).pos.x, movableArea.top});
}

void Deck::SetDeckList(int order)
{
	DECK_TABLE->SetFilePath(order);
	DECK_TABLE->Load();
	auto deckCards = DECK_TABLE->Get("DECK").deckList;
	int count = DECK_TABLE->Get("DECK").count;
	
	for (int j = 0; j < deckCards.size(); j++)
	{
		float rand = Utils::RandomValue();
		float percent = 0;
		for (int i = 0; i < deckCards[j].size(); i++)
		{
			if (i - 1 >= 0)
			{
				percent += deckCards[j][i - 1].second;
			}
			if (rand < deckCards[j][i].second + percent)
			{
				deckList.push_back(deckCards[j][i].first);
				break;
			}
		}		
	}
	
}

void Deck::ShowCard()
{
	ObjectPool<Card>* cardPool = scene->GetObjectPool();
	std::list<Card*>* cards = scene->GetCardList();

	Card* card = cardPool->Take();
	
	card->sortingOrder += scene->MaxCardOrder() +1;
	cards->push_back(card);

	card->CardSetting(deckList.front());
	deckList.pop_front();

	sf::Vector2f pos = Utils::RandomOnUnitCircle() * 200.f;
	sf::FloatRect rect;
	do
	{
		pos = Utils::RandomOnUnitCircle() * 200.f;
		card->SetPosition(position + pos);
		rect = card->GetGlobalBounds();
	} while (!movableArea.contains(position + pos) || !movableArea.contains({ rect.left, rect.top }) ||
		!movableArea.contains({ rect.left + rect.width, rect.top + rect.height }));
	

	scene->AddGo(card);
	deckCount--;
	count.setString(std::to_string(deckCount));
}

void Deck::Move()
{
	if (scene->topGoWorld != this)
	{
		return;
	}
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && isSelect)
	{
		sf::Vector2f mPos = scene->ScreenToWorld(InputMgr::GetMousePositionB()) - 
			scene->ScreenToWorld(InputMgr::GetMousePosition());
		SetPosition(position - mPos);
	}
}

void Deck::Collision()
{
	
}
