#include "stdafx.h"
#include "TitleScene.h"

TitleScene::TitleScene() : Scene(SceneIds::Title)
{

}

void TitleScene::Init()
{
	Scene::Init();
	
}

void TitleScene::Enter()
{
	worldView.setCenter(0.f, 0.f);
	worldView.setSize(FRAMEWORK.GetWindowSizeF());

	Scene::Enter();
}

void TitleScene::Exit()
{
	Scene::Exit();
}

void TitleScene::Update(float dt)
{
	Scene::Update(dt);
}

void TitleScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(rect);
}
