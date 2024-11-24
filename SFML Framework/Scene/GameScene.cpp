#include "stdafx.h"
#include "GameScene.h"
#include "PlayArea.h"
#include "Card.h"
#include "Deck.h"
#include "CombineTable.h"
#include "UiSys.h"

GameScene::GameScene() : Scene(SceneIds::Game)
{
	
}

void GameScene::Init()
{
	AddGo(new PlayArea());
	ui = AddGo(new UiSys());
	//deck = AddGo(new Deck());
	Scene::Init();
}

void GameScene::Enter()
{
	viewPos = FRAMEWORK.GetWindowSizeF();
	background.setTexture(TEXTURE_MGR.Get("graphics/playArea/backGround.png"));
	
	background.setPosition(FRAMEWORK.GetWindowCenterPos());
	Utils::SetOrigin(background, Origins::MC);

	worldView.setCenter(FRAMEWORK.GetWindowCenterPos());
	worldView.setSize(FRAMEWORK.GetWindowSizeF());

	uiView.setCenter(FRAMEWORK.GetWindowCenterPos());
	uiView.setSize(FRAMEWORK.GetWindowSizeF());

	CreateDeck(0);
	SetStatus(Status::Play);
	Scene::Enter();
}

void GameScene::Exit()
{
	for (auto card : cards)
	{
		RemoveGo(card);
		cardPool.Return(card);
	}
	cards.clear();

	for (auto deck : decks)
	{
		RemoveGo(deck);
		deckPool.Return(deck);
	}
	decks.clear();

	Scene::Exit();
}

void GameScene::Update(float dt)
{
	
	if (pause)
	{
		ui->Update(dt);
		ui->FixedUpdate(dt);
		return;
	}
		
	Scene::Update(dt);
	int count = 0;
	for (auto card :cards)
	{
		if (card->GetId() == "Villager")
			count++;
	}

	if (count < 1)
		SetStatus(Status::GameOver);
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		pause ? SetStatus(Status::Play) : SetStatus(Status::Pause);
	}  
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		GiveFood();
	}
	
}

void GameScene::FixedUpdate(float dt)
{
	if (pause)
		return;
	topGoWorld = nullptr;
	topGoUi = nullptr;

	auto uiMousePos = ScreenToUi(InputMgr::GetMousePosition());
	auto worldMousePos = ScreenToWorld(InputMgr::GetMousePosition());

	for (auto go : gameObjects)
	{
		if (go->sortingLayer == SortingLayers::UI)
		{
			if (go->GetGlobalBounds().contains(uiMousePos))
			{
				if (topGoUi == nullptr)
				{
					
				}

			}
		}
		else
		{
			if (go->sortingLayer == SortingLayers::Card)
			{
				if (go->GetGlobalBounds().contains(worldMousePos))
				{
					if (topGoWorld == nullptr || topGoWorld->sortingOrder < go->sortingOrder)
					{
						topGoWorld = go;
					}

				}
				if(go->GetIsSelect())
					topGoWorld = go;
			}
		}
	}

	
	SetSelectCard();
	if (deck != nullptr)
	{
		selectDeck = deck->GetIsSelect();
	}
	CloseUpDown(FRAMEWORK.GetRealDeltaTime());
	MoveScreen(dt);

	std::list<Card*> removeList;
	for (auto card : cards)
	{
		if (card->GetDurability() == 0)
			removeList.push_back(card); 
	}

	for (auto card : removeList)
	{
		ReturnCard(card);
	}

	Scene::FixedUpdate(dt);
}

void GameScene::Draw(sf::RenderWindow& window)
{
	const sf::View& saveView = window.getView();
	window.setView(worldView);
	window.draw(background);
	window.setView(saveView);

	Scene::Draw(window);
	
}

void GameScene::SetSelectCard()
{
	for (auto card : cards)
	{
		selectCard = card->GetIsSelect();
		if (selectCard)
		{
			this->card = card;
			break;
		}
	}

	for (auto deck : decks)
	{
		selectDeck = deck->GetIsSelect();
		if (selectDeck)
		{
			this->deck = deck;
			break;
		}
	}
}

void GameScene::CloseUpDown(float dt)
{
	int temp = InputMgr::GetMouseWheelScrolled();
	if (temp > 0)
	{
		viewPos.x > viewArea.left ? viewPos.x -= viewPos.x * dt * 10.f : viewPos.x;
		viewPos.y > viewArea.top ? viewPos.y -= viewPos.y * dt * 10.f : viewPos.y;
		if (viewPos.x < 0)
			viewPos.x = viewArea.left;
		if (viewPos.y < 0)
			viewPos.y = viewArea.top;
		worldView.setSize(viewPos);
	}
	else if (temp < 0)
	{
		viewPos.x < viewArea.width ? viewPos.x += viewPos.x * dt * 10.f : viewPos.x;
		viewPos.y < viewArea.height ? viewPos.y += viewPos.y * dt * 10.f : viewPos.y;
		if (viewPos.x > viewArea.width)
			viewPos.x = viewArea.width;
		if (viewPos.y > viewArea.height)
			viewPos.y = viewArea.height;
		worldView.setSize(viewPos);
	}
}

void GameScene::MoveScreen(float dt)
{
	if (!selectCard && !selectDeck && InputMgr::GetMouseButton(sf::Mouse::Left) )
	{
		sf::Vector2f mPos = ScreenToWorld(InputMgr::GetMousePositionB()) - ScreenToWorld(InputMgr::GetMousePosition());
		worldView.setCenter(worldView.getCenter().x + mPos.x, worldView.getCenter().y + mPos.y);
	}
		
}

void GameScene::ZoomCard(Card* card)
{
	worldView.setCenter(card->GetPosition());
}

void GameScene::Collision(Card* card, Deck* deck, float dt)
{
	sf::FloatRect cRect = card->GetGlobalBounds();
	sf::FloatRect dRect = deck->GetGlobalBounds();
	sf::Vector2f dPos = deck->GetPosition();
	sf::Vector2f cPos = card->GetPosition();
	if (Utils::CheckCollision(card->GetCardBody(), deck->GetBody()))
	{
		if (cRect.left > dPos.x)
		{
			cPos.x += (dRect.left + dRect.width - cRect.left) * dt * 5.f;
			card->SetPosition(cPos);
		}
		if (cRect.top > dPos.y)
		{
			cPos.y += (dRect.top - cRect.height + cRect.top) * dt * 5.f;
			card->SetPosition(cPos);
		}
		if (cRect.left + cRect.width < dPos.x)
		{
			cPos.x -= (dRect.left - cRect.left + cRect.width) * dt * 5.f;
			card->SetPosition(cPos);
		}
		if (cRect.top + cRect.height < dPos.y)
		{
			cPos.y -= (dRect.top - cRect.top + cRect.height) * dt * 10.f;
			card->SetPosition(cPos);
		}
	}
}

void GameScene::RemoveDeck(Deck* deck)
{
	RemoveGo(deck);
	deck = nullptr;
}

void GameScene::CreateDeck(int order)
{
	Deck* deck = new Deck();
	/*Deck* deck = deckPool.Take();*/
	deck->SetDeckOrder(order);
	deck->Reset();
	deck->sortingOrder = MaxCardOrder() + 1;
	decks.push_back(deck);
	//card->CardSetting("Villager");
	AddGo(deck);
}

void GameScene::ReturnCard(Card* card)
{
	if(card->GetCombineUp() != nullptr )
		card->GetCombineUp()->SetCombineDown(nullptr);
	if (card->GetCombineDown() != nullptr)
		card->GetCombineDown()->SetCombineUp(nullptr);

	card->SetCombineUp(nullptr);
	card->SetCombineDown(nullptr);


	RemoveGo(card);
	cardPool.Return(card);
	cards.remove(card);
	CheckCount();
	this->card = nullptr;
}

Card* GameScene::CreateCard(const std::string& id)
{
	Card* card = cardPool.Take();
	
	/*if (cards.size() == 0)
		card->sortingOrder = 0;
	else*/
	card->sortingOrder = MaxCardOrder() + 1;
	card->CardSetting(id);
	cards.push_back(card);
	CheckCount();
	return AddGo(card);
}

int GameScene::MaxCardOrder()
{
	int maxOrder = 0;
	for (auto go : gameObjects)
	{
		if (go->sortingLayer == SortingLayers::Card)
		{
			maxOrder = std::max(maxOrder, go->sortingOrder);
		}
	}
	for (auto addGo : addGameObjects)
	{
		if (addGo->sortingLayer == SortingLayers::Card)
		{
			if (addGo->sortingOrder > maxOrder)
				maxOrder = addGo->sortingOrder;
		}
	}
	return maxOrder;
}

void GameScene::SetCombineList()
{
	for (auto card : cards)
	{
		if (cardCombineList.size() == 0 )
		{
			std::vector<Card*> vec;
			vec.push_back(card);
			cardCombineList.push_back(vec);
		}
		for (auto i = cardCombineList.begin(); i != cardCombineList.end(); i++)
		{
			std::vector<Card*> temp = *i;
			if (std::find(temp.begin(), temp.end(), card) == temp.end())
			{
				std::vector<Card*> vec;
				vec.push_back(card);
				cardCombineList.push_back(vec);
			}

			if (card->GetCombineUp() == nullptr)
				continue;

			if (std::find(temp.begin(), temp.end(), card) == temp.end() &&
				std::find(temp.begin(), temp.end(), card->GetCombineUp()) != temp.end())
			{
				i->push_back(card);
			}

			if (std::find(temp.begin(), temp.end(), card) != temp.end() &&
				std::find(temp.begin(), temp.end(), card->GetCombineUp()) == temp.end())
			{
				i->erase(std::find(temp.begin(), temp.end(), card));
				if (i->size() < 1)
				{
					cardCombineList.remove(*i);
				}
			}
			
		}
	}
}

void GameScene::CheckCount()
{
	cardCnt = 0;
	maxCardCnt = 2;
	coinCnt = 0;
	needFood = 0;
	haveFood = 0;
	for (auto& card : cards)
	{
		if (card->GetId() != "Coin")
			cardCnt++;
		if (card->GetId() == "Shed")
		{
			maxCardCnt += 4;
		}
		if (card->GetId() == "Coin")
			coinCnt++;
		if (card->GetFoodEat() > 0)
			needFood += card->GetFoodEat();
		if (card->GetFoodGet() > 0)
			haveFood += card->GetFoodGet();
	}
	ui->SetFood(haveFood, needFood);
	ui->SetCoin(coinCnt);
	ui->SetCardCnt(cardCnt, maxCardCnt);
}

void GameScene::SetStatus(Status st)
{
	status = st;
	switch (status)
	{
	case GameScene::Status::Play:
		pause = false;
		break;
	case GameScene::Status::Pause:
		pause = true;
		break;
	case GameScene::Status::NextTurn:
		break;
	case GameScene::Status::GameOver:
		break;
	default:
		break;
	}
}

void GameScene::GiveFood()
{
	std::vector<Card*> villagers;
	std::list<Card*> foods;
	std::list<Card*> deleteFoods;
	for (auto card : cards)
	{
		if (card->GetId() == "Villager")
			villagers.push_back(card);
		if (card->GetFoodGet() > 0)
			foods.push_back(card);
	}

	for (auto food : foods)
	{
		for (int i = 0; i < villagers.size(); i++)
		{
			if (villagers[i]->GetFoodEat() > 0)
			{
				ZoomCard(villagers[i]);
				food->EatFood(villagers[i]);
				int temp = (int)Utils::Clamp(villagers[i]->GetFoodEat(), 0, food->GetFoodGet());
				food->SetFoodGet(food->GetFoodGet() - temp);
				villagers[i]->SetFoodEat(villagers[i]->GetFoodEat() - temp);
			}
			if (food->GetFoodGet() < 1)
			{
				deleteFoods.push_back(food);
				break;
			}
				
		}
	}

	for (auto deleteFood : deleteFoods)
	{
		ReturnCard(deleteFood);
	}

	for (auto villager : villagers)
	{
		if (villager->GetFoodEat() > 0)
			villager->IsDead();
		else
			villager->SetFoodEat(2);
	}

	for (auto card : cards)
	{
		card->SetCombineList();
	}
	CheckCount();
}
