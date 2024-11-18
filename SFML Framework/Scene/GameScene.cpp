#include "stdafx.h"
#include "GameScene.h"
#include "PlayArea.h"
#include "Card.h"
#include "Deck.h"

GameScene::GameScene() : Scene(SceneIds::Game)
{
	
}

void GameScene::Init()
{
	AddGo(new PlayArea());
	deck = AddGo(new Deck());
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

	Scene::Exit();
}

void GameScene::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		CrateCard();
	}
	selectDeck = deck->GetSelectDeck();
}

void GameScene::FixedUpdate(float dt)
{
	SetSelectCard();
	CloseUpDown(dt);
	MoveScreen(dt);
	for (auto& card : cards)
	{
		Collision(card, deck, dt);
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
		selectCard = card->GetSelectCard();
		if (selectCard)
		{
			this->card = card;
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

void GameScene::CrateCard()
{
	Card* card = cardPool.Take();
	cards.push_back(card);

	card->CardSetting();

	sf::Vector2f pos = FRAMEWORK.GetWindowCenterPos();
	card->SetPosition(pos);

	AddGo(card);
}
