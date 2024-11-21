#include "stdafx.h"
#include "GameScene.h"
#include "PlayArea.h"
#include "Card.h"
#include "Deck.h"
#include "CombineTable.h"

GameScene::GameScene() : Scene(SceneIds::Game)
{
	
}

void GameScene::Init()
{
	AddGo(new PlayArea());
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
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		CreateDeck(0);
		
	}
	
}

void GameScene::FixedUpdate(float dt)
{

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
	CloseUpDown(dt);
	MoveScreen(dt);
	/*for (auto& card : cards)
	{
		Collision(card, deck, dt);
	}*/

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
		std::cout << viewPos.x << " " << viewPos.y << std::endl;
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
	RemoveGo(card);
	cardPool.Return(card);
	cards.remove(card);
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
	std::cout << "card" << card->sortingOrder << std::endl;
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
