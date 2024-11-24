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
	hpStr.setPosition(body.getGlobalBounds().left + body.getGlobalBounds().width - 18.f,
		body.getGlobalBounds().top + body.getGlobalBounds().height - 18.f);
	cardName.setPosition(body.getGlobalBounds().left + 5.f, body.getGlobalBounds().top + 3.f);
	hpSprite.setPosition(body.getGlobalBounds().left + body.getGlobalBounds().width - 5.f, 
		body.getGlobalBounds().top + body.getGlobalBounds().height - 3.f);
	coinStr.setPosition(body.getGlobalBounds().left + 13.f,
		body.getGlobalBounds().top + body.getGlobalBounds().height - 15.f);
	coin.setPosition(body.getGlobalBounds().left + 6.f,
		body.getGlobalBounds().top + body.getGlobalBounds().height - 6.f);
	foodStr.setPosition(body.getGlobalBounds().left + body.getGlobalBounds().width - 18.f,
		body.getGlobalBounds().top + body.getGlobalBounds().height - 23.f);
	foodSprite.setPosition(body.getGlobalBounds().left + body.getGlobalBounds().width - 5.f,
		body.getGlobalBounds().top + body.getGlobalBounds().height - 5.f);
	//timeBar.SetPosition({ topCardPos.x + GetGlobalBounds().width * 0.5f, topCardPos.y - 3.f });
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
	
}

void Card::Update(float dt)
{
	SetSelectCard();
	CheckCombine();
	GetIsCombine();
	if (StartCombine)
	{
		timeBar.sortingOrder = this->sortingOrder;
		timeBar.SetActive(true);
		CombineAction(dt);
	}
	else
	{
		timeBar.SetActive(false);
		timer = 0;
	}
		
		
}

void Card::FixedUpdate(float dt)
{
	Move(dt);
	MoveInArea();
	CombineCard();
}

void Card::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(cardName);
	window.draw(icon);
	if (VILLAGER_TABLE->Get(this->id).health != -1)
	{
		window.draw(hpSprite);
		window.draw(hpStr);
	}
	if (VILLAGER_TABLE->Get(this->id).foodGet != -1)
	{
		window.draw(foodSprite);
		window.draw(foodStr);
	}
	if (VILLAGER_TABLE->Get(this->id).useCoinIcon != "NONE")
	{
		window.draw(coin);
	}
	if (VILLAGER_TABLE->Get(this->id).value != -1)
	{
		window.draw(coinStr);
	}
	if (timeBar.IsActive())
	{
		timeBar.Draw(window);
	}
	hitbox.Draw(window);
}

void Card::SetSelectCard()
{

	sf::Vector2f mousePos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(InputMgr::GetMousePosition());
	std::list<Card*>* cards = scene->GetCardList();
	if (body.getGlobalBounds().contains(mousePos) && InputMgr::GetMouseButtonDown(sf::Mouse::Left) && scene->topGoWorld == this)
	{	
		sortingOrder = scene->MaxCardOrder() + 1;
		isSelect = true;
		if (combineDown != nullptr)
		{
			combineDown->combineUp = nullptr;
		}
		if (combineUp != nullptr)
		{
			combineUp->combineDown = nullptr;
		}
		combineDown = nullptr;
		combineUp = nullptr;
		timer = 0;
		StartCombine = false;
	}
	else if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
		isSelect = false;
	}
		
}

void Card::CardSetting(std::string id)
{
	this->id = id;
	
	body.setTexture(TEXTURE_MGR.Get(VILLAGER_TABLE->Get(this->id).cardColor));
	SetOrigin(Origins::MC);
	body.setScale(0.22f, 0.22f);

	icon.setTexture(TEXTURE_MGR.Get(VILLAGER_TABLE->Get(this->id).iconTex), true);
	Utils::SetOrigin(icon, Origins::MC);
	icon.setScale(0.05f, 0.05f);

	cardName.setFont(font);
	cardName.setString(VILLAGER_TABLE->Get(this->id).name);
	cardName.setCharacterSize(150);
	cardName.setScale(0.1f, 0.1f);
	cardName.setFillColor(sf::Color::Black);
	cardName.setStyle(sf::Text::Bold);

	health = VILLAGER_TABLE->Get(this->id).health;
	hpStr.setFont(font);
	hpStr.setString(std::to_string(health));
	hpStr.setCharacterSize(150);
	hpStr.setScale(0.07f, 0.07f);
	hpStr.setFillColor(sf::Color::White);
	hpStr.setStyle(sf::Text::Bold);
	Utils::SetOrigin(hpStr, Origins::MC);

	hpSprite.setTexture(TEXTURE_MGR.Get("graphics/icon/Ui_Hart.png"));
	hpSprite.setColor(sf::Color::Black);
	hpSprite.setScale(0.05f, 0.05f);
	Utils::SetOrigin(hpSprite, Origins::BR);

	value = VILLAGER_TABLE->Get(this->id).value;
	coinStr.setFont(font);
	coinStr.setString(std::to_string(value));
	coinStr.setCharacterSize(150);
	coinStr.setScale(0.07f, 0.07f);
	coinStr.setFillColor(sf::Color::Black);
	coinStr.setStyle(sf::Text::Bold);
	Utils::SetOrigin(coinStr, Origins::BL);

	if (VILLAGER_TABLE->Get(this->id).useCoinIcon != "NONE")
	{
		coin.setTexture(TEXTURE_MGR.Get(VILLAGER_TABLE->Get(this->id).useCoinIcon));
		coin.setColor(sf::Color::Black);
		coin.setScale(0.05f, 0.05f);
		coinStr.setFillColor(sf::Color::White);
		Utils::SetOrigin(coin, Origins::BL);
	}

	foodGet = VILLAGER_TABLE->Get(this->id).foodGet;
	foodStr.setFont(font);
	foodStr.setString(std::to_string(foodGet));
	foodStr.setCharacterSize(150);
	foodStr.setScale(0.07f, 0.07f);
	foodStr.setFillColor(sf::Color::White);
	foodStr.setStyle(sf::Text::Bold);
	Utils::SetOrigin(hpStr, Origins::MC);

	foodSprite.setTexture(TEXTURE_MGR.Get("graphics/icon/UI_Bread.png"));
	foodSprite.setColor(sf::Color::Black);
	foodSprite.setScale(0.05f, 0.05f);
	Utils::SetOrigin(foodSprite, Origins::BR);

	attackSpeed = VILLAGER_TABLE->Get(this->id).attackSpeed;
	hitChance = VILLAGER_TABLE->Get(this->id).hitChance;
	damage = VILLAGER_TABLE->Get(this->id).damage;
	foodEat = VILLAGER_TABLE->Get(this->id).foodEat;
	durability = VILLAGER_TABLE->Get(this->id).durability;
	
	SetPosition(FRAMEWORK.GetWindowCenterPos());
}

void Card::Move(float dt)
{
	if (scene->topGoWorld != this)
	{
		return;
	}

	if (InputMgr::GetMouseButton(sf::Mouse::Left) && isSelect)
	{
		sf::Vector2f mPos = //scene->ScreenToWorld(InputMgr::GetMousePositionB()) -
			scene->ScreenToWorld(InputMgr::GetMousePosition());
		//SetPosition(position - mPos);
		sf::Vector2f direction = Utils::GetNormal(mPos - position);
		position.x = Utils::Clamp(position.x + direction.x * 500.f * dt, mPos.x, mPos.x);
		position.y = Utils::Clamp(position.y + direction.x * 500.f * dt, mPos.y, mPos.y);
		SetPosition(position);
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
	if (scene->topGoWorld != this)
	{
		return;
	}

	for (auto& card : *scene->GetCardList())
	{
		if (card == this)
			continue;
		if (card->GetGlobalBounds().intersects(this->GetGlobalBounds()) && InputMgr::GetMouseButtonUp(sf::Mouse::Left))
		{
			if (card->combineDown == nullptr)
			{
				card->combineDown = this;
				this->combineUp = card;
				SetCombineList();
				SetPosition({ card->GetPosition().x , card->GetPosition().y + 23.f });
				break;
			}
			else
				continue;
		}
	}
	
}

void Card::SetCombineList()
{
	std::vector<Card*> tempList;
	table.clear();
	table.insert({ id, 1 });

	Card* tempUp = combineUp;
	Card* tempDown = combineDown;
	tempList.push_back(this);

	topCardPos = { GetGlobalBounds().left, GetGlobalBounds().top };

	while (tempUp != nullptr)
	{
		tempList.push_back(tempUp);
		if (tempUp->combineUp == nullptr)
			topCardPos = { tempUp->GetGlobalBounds().left, tempUp->GetGlobalBounds().top };
		auto find = table.find(tempUp->id);
		if (find != table.end())
		{
			table[tempUp->id]++;
			tempUp = tempUp->combineUp;
		}
		else
		{
			table.insert({ tempUp->id, 1 });
			tempUp = tempUp->combineUp;
		}
	}
	while (tempDown != nullptr)
	{
		tempList.push_back(tempDown);
		auto find = table.find(tempDown->id);
		if (find != table.end())
		{
			table[id]++;
			tempDown = tempDown->combineDown;
		}
		else
		{
			table.insert({ tempDown->id, 1 });
			tempDown = tempDown->combineDown;
		}
	}
	scene->cardCombineList.push_back(tempList);
}

void Card::CheckCombine()
{
	Card* tempUp = combineUp;

	while (tempUp == nullptr)
	{
		return;
	}
	
	std::unordered_map<std::string, DataCombine> chek = COMBINE_TABLE->Get();
	for (auto iter = chek.begin(); iter != chek.end(); iter++) 
	{
		bool combineOk = false;
		for (int i = 0; i < iter->second.count; i++)
		{
			StartCombine = false;
			auto find = table.find(iter->second.kinds[i].first);
			if (find == table.end())
			{
				StartCombine = false;
				break;
			}
			if (iter->second.kinds[i].second > find->second)
			{
				StartCombine = false;
				break;
			}
			StartCombine = true;
		}
		if (StartCombine)
		{
			resultId = iter->first;
			combineTime = iter->second.time;
			timeBar.SetType(Timer::Type::CombineTimer);
			timeBar.SetMaxTime(combineTime);
			timeBar.SetPosition({ topCardPos.x + GetGlobalBounds().width * 0.5f, topCardPos.y - 3.f });
			break;
		}
	}
	
}

void Card::CombineAction(float dt)
{
	timer += dt;
	timeBar.SetTimeBar(timer);
	if (timer > combineTime)
	{
		Card* create = scene->CreateCard(resultId);
		create->SetPosition(position + Utils::RandomOnUnitCircle() * 200.f);
		create->MoveInArea();
		timer = 0;
		timeBar.SetActive(false);
		Card* tempUp = combineUp;
		Card* tempDown = combineDown;
		while (tempUp != nullptr)
		{
			if (table.find(tempUp->id) != table.end() && tempUp->durability > 0)
			{
				tempUp->durability--;
			}
			tempUp = tempUp->combineUp;
		}
		if (this->durability > 0)
			this->durability--;
		while (tempDown != nullptr)
		{
			if (tempDown->durability > 0)
			{
				tempDown->durability--;
			}
			tempDown = tempDown->combineDown;
		}
	}
		
}

void Card::GetIsCombine()
{
	Card* tempUp = combineUp;
	Card* tempDown = combineDown;

	if (tempUp == nullptr && tempDown == nullptr)
	{
		StartCombine = false;
	}

	while (tempUp != nullptr)
	{
		if (tempUp->StartCombine)
		{
			StartCombine = false;
			return;
		}
		else
			tempUp = tempUp->combineUp;
	}
	while (tempDown != nullptr)
	{
		if (tempDown->StartCombine)
		{
			StartCombine = false;
			return;
		}
		else
			tempDown = tempDown->combineDown;
	}
}

void Card::IsDead()
{
	this->id = "Corpse";
	body.setTexture(TEXTURE_MGR.Get("graphics/card/Corpse.png"));
	SetOrigin(Origins::MC);
	body.setScale(0.22f, 0.22f);

	cardName.setFont(font);
	cardName.setString(L"½ÃÃ¼");
	cardName.setCharacterSize(150);
	cardName.setScale(0.1f, 0.1f);
	cardName.setFillColor(sf::Color::Black);
	cardName.setStyle(sf::Text::Bold);

	value = -1;
	isCombine = false;
	StartCombine = false;

	isDie = true;
	health = 0;
	attackSpeed = 0;
	hitChance = 0;
	damage = 0;
	foodEat = 0;
	foodGet = -1;
	value = -1;
	durability = 3;

	resultId = "";
	combineTime = 0;
	timer = 0;

	icon = sf::Sprite();

	hpSprite = sf::Sprite();
	hpStr = sf::Text();
	coin = sf::Sprite();;
	coinStr = sf::Text();;

	foodSprite = sf::Sprite();;
	foodStr = sf::Text();;
}

void Card::EatFood(Card* card)
{
	while (position != card->GetPosition())
	{
		sf::Vector2f direction = Utils::GetNormal(card->GetPosition() - position);
		position.x = Utils::Clamp(position.x + direction.x * FRAMEWORK.GetRealDeltaTime(), 
			card->GetPosition().x, card->GetPosition().x);
		position.y = Utils::Clamp(position.y + direction.x * FRAMEWORK.GetRealDeltaTime(),
			card->GetPosition().y, card->GetPosition().y);
		SetPosition(position);
	}
	
}
