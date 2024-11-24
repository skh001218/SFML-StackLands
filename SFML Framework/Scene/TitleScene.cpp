#include "stdafx.h"
#include "TitleScene.h"
#include "TileMap.h"

TitleScene::TitleScene() : Scene(SceneIds::Title)
{

}

void TitleScene::Init()
{
	menu = AddGo(new TileMap());
	Scene::Init();
	
}

void TitleScene::Enter()
{
	worldView.setCenter(FRAMEWORK.GetWindowCenterPos());
	worldView.setSize(FRAMEWORK.GetWindowSizeF());

	uiView.setCenter(FRAMEWORK.GetWindowCenterPos());
	uiView.setSize(FRAMEWORK.GetWindowSizeF());

	Scene::Enter();

	menu->SetOrigin(Origins::BL);
	menu->SetPosition({ 0, FRAMEWORK.GetWindowSizeF().y });
	background.setTexture(TEXTURE_MGR.Get("graphics/playArea/backGround.png"));

	next.clear();
	isChange = false;
	menuStr.clear();

	backStr.clear();
	lines.clear();

	SetMenu();
	SetBackMenuStr();

	
	
}

void TitleScene::Exit()
{
	Scene::Exit();
}

void TitleScene::Update(float dt)
{
	if (isChange)
	{
		ChangeScene(dt);
		if (next[0].getSize().y > 54.f)
		{
			isChange = false;
			next.clear();
			SCENE_MGR.ChangeScene(SceneIds::Game);
		}
		return;
	}
	Scene::Update(dt);
}

void TitleScene::FixedUpdate(float dt)
{
	auto worldMousePos = ScreenToWorld(InputMgr::GetMousePosition());

	for (int i = 0; i < 4; i++)
	{
		if (backStr[i].getGlobalBounds().contains(worldMousePos))
		{
			lines[i].setFillColor(sf::Color::Black);
			lines[i].setSize({ menuStr[i + 1].getGlobalBounds().width, 3.f });
			lines[i].setPosition(menuStr[i + 1].getGlobalBounds().left, menuStr[i + 1].getGlobalBounds().top + menuStr[i + 1].getGlobalBounds().height + 5.f);

			backStr[i].setFillColor(sf::Color(255, 244, 206));
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				DoAction(i);
			}
		}
		else
		{
			lines[i].setSize({ 0, 0 });
			backStr[i].setFillColor(sf::Color::Transparent);
		}
	}
}

void TitleScene::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	
	Scene::Draw(window);
	window.draw(menuLine);
	
	for (auto& back : backStr)
		window.draw(back);
	for (auto& tex : menuStr)
		window.draw(tex);
	for (auto& line : lines)
		window.draw(line);
	for (auto& n : next)
		window.draw(n);
}

void TitleScene::SetMenu()
{
	sf::FloatRect rect = menu->GetGlobalBounds();
	for (int i = 0; i < 5; i++)
	{
		menuStr.push_back(sf::Text());
		menuStr[i].setFont(FONT_MGR.Get("fonts/NotoSansKR-Medium.otf"));
		menuStr[i].setFillColor(sf::Color::Black);
	}
	menuStr[0].setString("Stacklands");
	menuStr[0].setPosition({rect.left + 20.f, rect.top + 30.f});
	menuStr[0].setCharacterSize(80);
	menuStr[0].setStyle(sf::Text::Bold);

	menuLine.setTexture(TEXTURE_MGR.Get("graphics/playArea/sketchy_box_line.png"));
	menuLine.setColor(sf::Color::Black);
	menuLine.setScale({ 1.80f, 1.f});
	Utils::SetOrigin(menuLine, Origins::TL);
	menuLine.setPosition(menuStr[0].getGlobalBounds().left, menuStr[0].getGlobalBounds().top + menuStr[0].getGlobalBounds().height + 5.f);

	menuStr[1].setString(L"새로운 운영 시작");
	menuStr[1].setPosition({ rect.left + 30.f, menuStr[0].getPosition().y + 150.f});
	menuStr[1].setCharacterSize(32);
	menuStr[1].setStyle(sf::Text::Bold);

	menuStr[2].setString(L"카드 백과사전");
	menuStr[2].setPosition({ rect.left + 30.f, menuStr[1].getPosition().y + 100.f });
	menuStr[2].setCharacterSize(32);
	menuStr[2].setStyle(sf::Text::Bold);

	menuStr[3].setString(L"옵션");
	menuStr[3].setPosition({ rect.left + 30.f, menuStr[2].getPosition().y + 60.f });
	menuStr[3].setCharacterSize(32);
	menuStr[3].setStyle(sf::Text::Bold);

	menuStr[4].setString(L"종료");
	menuStr[4].setPosition({ rect.left + 30.f, menuStr[3].getPosition().y + 100.f });
	menuStr[4].setCharacterSize(32);
	menuStr[4].setStyle(sf::Text::Bold);

	
}

void TitleScene::SetBackMenuStr()
{
	
	for (int i = 0; i < 4; i++)
	{
		sf::FloatRect rect = menuStr[i + 1].getGlobalBounds();
		backStr.push_back(sf::RectangleShape({menuLine.getGlobalBounds().width, rect.height + 20.f }));
		backStr[i].setPosition({ rect.left - 10.f, rect.top - 13.f });

		lines.push_back(sf::RectangleShape());
	}
}

void TitleScene::DoAction(int i)
{
	switch (i)
	{
	case 0:
		isChange = true;
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		FRAMEWORK.GetWindow().close();
		break;
	default:
		break;
	}
}

void TitleScene::ChangeScene(float dt)
{
	
	for (int i = 0; i < 200; i++)
	{
		next.push_back(sf::RectangleShape({3000.f, 0.f}));
		next[i].setPosition({ -100.f, i * 54.f });
		next[i].setFillColor(sf::Color::Black);
		next[i].setRotation(-45);
		next[i].setSize({ 3000.f, next[i].getSize().y + 54.f * dt * 0.8f});
	}
}
