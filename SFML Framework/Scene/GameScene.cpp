#include "stdafx.h"
#include "GameScene.h"
#include "PlayArea.h"
#include "Card.h"

GameScene::GameScene() : Scene(SceneIds::Title)
{
	
}

void GameScene::Init()
{
	AddGo(new PlayArea());
	card = AddGo(new Card("Card"));
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
	Scene::Exit();
}

void GameScene::Update(float dt)
{
	Scene::Update(dt);
}

void GameScene::FixedUpdate(float dt)
{
	sf::Vector2f mouse = ScreenToWorld(InputMgr::GetMousePosition());
	selectCard = card->GetSelectCard();
	CloseUpDown(dt);
	MoveScreen(dt);
	MoveCard(card);

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

void GameScene::CloseUpDown(float dt)
{
	int temp = InputMgr::GetMouseWheelScrolled();
	if (temp > 0)
	{
		viewPos.x > viewArea.left ? viewPos.x -= viewPos.x * dt * 10.f : viewPos.x;
		viewPos.y > viewArea.top ? viewPos.y -= viewPos.y * dt * 10.f : viewPos.y;
		worldView.setSize(viewPos);
	}
	else if (temp < 0)
	{
		viewPos.x < viewArea.width ? viewPos.x += viewPos.x * dt * 10.f : viewPos.x;
		viewPos.y < viewArea.height ? viewPos.y += viewPos.y * dt * 10.f : viewPos.y;
		worldView.setSize(viewPos);
	}
}

void GameScene::MoveScreen(float dt)
{
	if (!selectCard && InputMgr::GetMouseButton(sf::Mouse::Left) )
	{
		sf::Vector2f mPos = ScreenToWorld(InputMgr::GetMousePositionB()) - ScreenToWorld(InputMgr::GetMousePosition());
		worldView.setCenter(worldView.getCenter().x + mPos.x, worldView.getCenter().y + mPos.y);
	}
		
}

void GameScene::MoveCard(Card* card)
{
	if (InputMgr::GetMouseButton(sf::Mouse::Left) && selectCard)
	{
		sf::Vector2f mPos = ScreenToWorld(InputMgr::GetMousePositionB()) - ScreenToWorld(InputMgr::GetMousePosition());
		card->SetPosition(card->GetPosition() - mPos);
	}
}
