#include "stdafx.h"
#include "GameScene.h"
#include "PlayArea.h"

GameScene::GameScene() : Scene(SceneIds::Title)
{

}

void GameScene::Init()
{
	AddGo(new PlayArea());
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
	CloseUpDown(dt);
	MoveScreen(dt);
	Scene::Update(dt);
}

void GameScene::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);
	window.draw(background);
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
	if (InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		sf::Vector2f mPos = (sf::Vector2f)(InputMgr::GetMousePositionB() - InputMgr::GetMousePosition());
		worldView.setCenter(worldView.getCenter().x + mPos.x, worldView.getCenter().y + mPos.y);
		std::cout << mPos.x << " , " << mPos.y << std::endl;
	}
		
}
