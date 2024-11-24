#include "stdafx.h"
#include "UiSys.h"
#include "GameScene.h"

UiSys::UiSys(const std::string& name)
	: GameObject(name)
{
	
}

void UiSys::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	timeBar.SetPosition(position);
}

void UiSys::SetRotation(float angle)
{
	rotation = angle;
	timeBar.SetRotation(rotation);
}

void UiSys::SetScale(const sf::Vector2f& s)
{
	scale = s;
	timeBar.SetScale(scale);
}

void UiSys::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		timeBar.SetOrigin(originPreset);
	}
}

void UiSys::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	timeBar.SetOrigin(origin);
}

void UiSys::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void UiSys::Release()
{
}

void UiSys::Reset()
{
	curProgress = 0;
	startMonth = true;
	foodEatTime = 0;
	dieTime = 0;
	completeTime = 0;
	isProgress = false;
	isEnd = false;
	scene = dynamic_cast<GameScene*>(SCENE_MGR.GetCurrentScene());
	months = 1;
	curImage = 0;
	SetTimeBar();
	SetStatus();
}

void UiSys::Update(float dt)
{
	if (isProgress)
	{
		if (curProgress == 1)
		{
			foodEatTime += dt;
			text2.setString(L"식사중...");
			menuStr.setString("");
			lines.setSize({ 0, 0 });
			backStr.setFillColor(sf::Color::Transparent);
			if (foodEatTime > 3)
				InputMsg();
		}
		if (curProgress == 3)
		{
			dieTime += dt;
			menuStr.setString("");
			lines.setSize({ 0, 0 });
			backStr.setFillColor(sf::Color::Transparent);
			if (dieTime > 2)
			{
				scene->GiveFood();
				text2.setString(L"모두 굶어 죽었습니다!");
				menuStr.setString(L"게임 종료");
				curProgress = 9;
			}
		}
		if (curProgress == 4)
		{
			completeTime += dt;
			menuStr.setString("");
			lines.setSize({ 0, 0 });
			backStr.setFillColor(sf::Color::Transparent);
			if (completeTime > 2)
			{
				months++;
				scene->GiveFood();
				if (haveCard > maxCard)
				{
					text2.setString(std::to_wstring(haveCard - maxCard) + L"장의 카드가 초과되었습니다!");
					menuStr.setString(L"카드" + std::to_wstring(haveCard - maxCard) + L"장 판매");
					curProgress = 6;
					return;
				}
				text1.setString(std::to_wstring(months) + L"번째 달 시작");
				text2.setString("");
				menuStr.setString(L"새로운 달 시작");
				curProgress = 5;
			}
		}
		if (curProgress == 7)
		{
			FRAMEWORK.SetTimeScale(0);
			scene->SetStatus(GameScene::Status::Play);
			text2.setString(std::to_wstring(haveCard - maxCard) + L"장의 카드가 초과되었습니다!");
			menuStr.setString(L"카드" + std::to_wstring(haveCard - maxCard) + L"장 판매");
			if (maxCard >= haveCard)
			{
				text1.setString(std::to_wstring(months) + L"번째 달 시작");
				text2.setString("");
				menuStr.setString(L"새로운 달 시작");
				curProgress = 5;
			}
		}
		if (curProgress == 9)
		{
			progressBar.SetPosition({ progressBar.GetPosition().x - 700.f * dt,progressBar.GetPosition().y });
			text1.setPosition({ text1.getPosition().x - 700.f * dt,progressBar.GetPosition().y });
			text2.setPosition({ text2.getPosition().x - 700.f * dt,progressBar.GetPosition().y });
			menuStr.setPosition({ menuStr.getPosition().x - 700.f * dt,progressBar.GetPosition().y });
			backStr.setPosition({ backStr.getPosition().x - 700.f * dt,progressBar.GetPosition().y });
			lines.setPosition({ lines.getPosition().x - 700.f * dt,progressBar.GetPosition().y });
			if (progressBar.GetGlobalBounds().left + progressBar.GetGlobalBounds().width < -100.f)
			{
				SetEndProgress();
				curProgress = 10;
			}

		}

		if (backStr.getGlobalBounds().contains(scene->ScreenToUi(InputMgr::GetMousePosition())))
		{
			lines.setFillColor(sf::Color::Black);
			lines.setSize({ menuStr.getGlobalBounds().width, 3.f });
			lines.setPosition(menuStr.getGlobalBounds().left, menuStr.getGlobalBounds().top + menuStr.getGlobalBounds().height + 5.f);

			backStr.setFillColor(sf::Color(255, 244, 206));
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				if (menuStr.getString() == L"주민에게 음식 제공")
				{
					curProgress = 1;
				}
				else if (menuStr.getString() == L"이런!")
				{
					curProgress = 3;
				}
				else if (menuStr.getString() == L"새로운 달 시작")
				{
					isProgress = false;
					isEnd = false;
					curProgress = 0;
					startMonth = true;
					curTime = 0;
					curImage = 0;
					playBtn.setTexture(TEXTURE_MGR.Get(images[0]), true);
					Utils::SetOrigin(playBtn, Origins::MR);
					playBtn.setPosition(timeBar.GetGlobalBounds().left + timeBar.GetGlobalBounds().width - 20.f,
						timeBar.GetGlobalBounds().height * 0.5f);
					FRAMEWORK.SetTimeScale(1);
					scene->SetStatus(GameScene::Status::Play);
					SetMonth(months);
				}
				else if (menuStr.getString() == L"카드" + std::to_wstring(haveCard - maxCard) + L"장 판매")
				{
					curProgress = 7;
				}
				else if (menuStr.getString() == L"게임 종료")
				{
					isEnd = true;
					curProgress = 9;
				}
				else if (menuStr.getString() == L"메뉴로 돌아가기")
				{
					SCENE_MGR.ChangeScene(SceneIds::Title);
				}

			}
		}
		else
		{
			lines.setSize({ 0, 0 });
			backStr.setFillColor(sf::Color::Transparent);
		}
	}
	if (startMonth)
	{
		curTime += dt;
		float value = curTime / 30.f;
		sf::Vector2f maxSize = { timeBar.GetGlobalBounds().width - 6.f, timeBar.GetGlobalBounds().height - 6.f };
		time.setSize({ Utils::Clamp(maxSize.x * value, 0, maxSize.x), maxSize.y });
		if (value > 1)
			NextTrun();
	}
	
	if (playBtn.getGlobalBounds().contains(scene->ScreenToUi(InputMgr::GetMousePosition())) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		curImage++;
		if (curImage > 2)
			curImage = 0;
		switch (curImage)
		{
		case 0:
			FRAMEWORK.SetTimeScale(1);
			break;
		case 1:
			FRAMEWORK.SetTimeScale(2);
			break;
		case 2:
			FRAMEWORK.SetTimeScale(0);
			break;
		default:
			break;
		}
		playBtn.setTexture(TEXTURE_MGR.Get(images[curImage]), true);
		Utils::SetOrigin(playBtn, Origins::MR);
		playBtn.setPosition(timeBar.GetGlobalBounds().left + timeBar.GetGlobalBounds().width - 20.f,
			timeBar.GetGlobalBounds().height * 0.5f);
	}
}

void UiSys::Draw(sf::RenderWindow& window)
{
	if (!isProgress && !isEnd)
	{
		timeBar.Draw(window);
		window.draw(time);
		window.draw(month);
		window.draw(playBtn);
		statusBar.Draw(window);

		window.draw(food);
		window.draw(foodSp);

		window.draw(coin);
		window.draw(coinSp);

		window.draw(card);
		window.draw(cardSp);
	}
	else if (isProgress && !isEnd)
	{
		progressBar.Draw(window);
		window.draw(backStr);

		window.draw(text1);
		window.draw(text2);
		window.draw(menuStr);
		window.draw(lines);
	}
	else if (isEnd)
	{

	}

}

void UiSys::SetTimeBar()
{
	timeBar.Reset();
	timeBar.Set({ 8, 2 }, { 44.f, 44.f });
	timeBar.SetScale({ 1.f,0.6f });
	timeBar.SetOrigin(Origins::TR);
	timeBar.SetPosition({ FRAMEWORK.GetWindowSizeF().x, 0 });

	time.setSize({ 0.f, timeBar.GetGlobalBounds().height - 6.f });
	time.setFillColor(sf::Color(233, 223, 187));
	time.setPosition(timeBar.GetGlobalBounds().left + 3.f, timeBar.GetGlobalBounds().top + 3.f);

	month.setFont(FONT_MGR.Get("fonts/NotoSansKR-Medium.otf"));
	month.setString(std::to_wstring(months) + L"번째 달");
	month.setCharacterSize(22);
	month.setFillColor(sf::Color::Black);
	month.setStyle(sf::Text::Bold);
	Utils::SetOrigin(month, Origins::ML);
	month.setPosition(timeBar.GetGlobalBounds().left + 10.f, timeBar.GetGlobalBounds().height * 0.5f);

	playBtn.setTexture(TEXTURE_MGR.Get(images[curImage]), true);
	playBtn.setScale({0.04,0.04});
	playBtn.setColor(sf::Color::Black);
	Utils::SetOrigin(playBtn, Origins::MR);
	playBtn.setPosition(timeBar.GetGlobalBounds().left + timeBar.GetGlobalBounds().width - 20.f, 
		timeBar.GetGlobalBounds().height * 0.5f);
}

void UiSys::SetMonth(int month)
{
	months = month;
	this->month.setString(std::to_wstring(months) + L"번째 달");
	Utils::SetOrigin(this->month, Origins::ML);
}

void UiSys::SetStatus()
{
	statusBar.Reset();
	statusBar.Set({ 8, 2 }, { 44.f, 44.f });
	statusBar.SetScale({ 1.f,0.6f });
	statusBar.SetOrigin(Origins::TR);
	statusBar.SetPosition({ timeBar.GetGlobalBounds().left - 10.f, 0 });

	SetFood(haveFood, needFood);
	food.setCharacterSize(22);
	food.setFillColor(sf::Color::Black);
	//food.setStyle(sf::Text::Bold);

	foodSp.setTexture(TEXTURE_MGR.Get("graphics/icon/foodicon.png"));
	foodSp.setScale(0.05f, 0.05f);
	foodSp.setColor(sf::Color::Black);
	Utils::SetOrigin(foodSp, Origins::TL);

	SetCoin(haveCoin);
	coin.setCharacterSize(22);
	coin.setFillColor(sf::Color::Black);
	//coin.setStyle(sf::Text::Bold);

	coinSp.setTexture(TEXTURE_MGR.Get("graphics/icon/goldicon.png"));
	coinSp.setScale(0.05f, 0.05f);
	coinSp.setColor(sf::Color::Black);
	Utils::SetOrigin(coinSp, Origins::TL);

	SetCardCnt(haveCard, maxCard);
	card.setCharacterSize(22);
	card.setFillColor(sf::Color::Black);
	//card.setStyle(sf::Text::Bold);

	cardSp.setTexture(TEXTURE_MGR.Get("graphics/icon/cardicon.png"));
	cardSp.setScale(0.35f, 0.35f);
	cardSp.setColor(sf::Color::Black);
	Utils::SetOrigin(cardSp, Origins::TL);
}

void UiSys::SetFood(int foods1, int foods2)
{
	haveFood = foods1;
	needFood = foods2;
	food.setFont(FONT_MGR.Get("fonts/NotoSansKR-Medium.otf"));
	food.setString(std::to_wstring(haveFood) + L"/" + std::to_wstring(needFood));
	Utils::SetOrigin(food, Origins::TL);
	food.setPosition(statusBar.GetGlobalBounds().left + 15.f, statusBar.GetGlobalBounds().height * 0.25f);
	foodSp.setPosition(food.getPosition().x + food.getLocalBounds().width + 10.f, food.getPosition().y);
}

void UiSys::SetCoin(int coins)
{
	haveCoin = coins;
	coin.setFont(FONT_MGR.Get("fonts/NotoSansKR-Medium.otf"));
	coin.setString(std::to_wstring(haveCoin));
	Utils::SetOrigin(coin, Origins::TL);
	coin.setPosition(foodSp.getPosition().x + foodSp.getGlobalBounds().width + 20.f, foodSp.getPosition().y);
	coinSp.setPosition(coin.getPosition().x + coin.getGlobalBounds().width + 10.f, coin.getPosition().y + 2.f);
	

}

void UiSys::SetCardCnt(int cards1, int cards2)
{
	haveCard = cards1;
	maxCard = cards2;
	card.setFont(FONT_MGR.Get("fonts/NotoSansKR-Medium.otf"));
	card.setString(std::to_wstring(haveCard) + L"/" + std::to_wstring(maxCard));
	Utils::SetOrigin(card, Origins::TL);
	card.setPosition(coinSp.getPosition().x + coinSp.getGlobalBounds().width + 20.f, food.getPosition().y);
	cardSp.setPosition(card.getPosition().x + card.getGlobalBounds().width + 10.f, card.getPosition().y + 2.f);
}

void UiSys::NextTrun()
{
	startMonth = false;
	scene->SetStatus(GameScene::Status::Pause);
	curTime = 0;
	SetProgressBar();
	isProgress = true;

}

void UiSys::InputMsg()
{
	int count = 0;
	std::list<Card*> cards = *scene->GetCardList();
	if (haveFood < needFood)
	{
		(needFood - haveFood) % 2 == 1 ? count = count / 2 + 1 : count = count / 2;
		text1.setString(std::to_wstring(months) + L"번째 달 끝");
		text2.setString(L"식량이 부족합니다... 주민 " + std::to_wstring(count)+L"명이 굶어 죽습니다.");
		menuStr.setString(L"이런!");
		curProgress = 2;
		return;
	}
	
	text1.setString(std::to_wstring(months) + L"번째 달 끝");
	text2.setString(L"모두가 식사를 완료했습니다.");
	curProgress = 4;
		
}

void UiSys::SetProgressBar()
{
	progressBar.Reset();
	progressBar.Set({ 16, 5 }, { 44.f, 44.f });
	progressBar.SetScale({ 1.f,1.f });
	progressBar.SetOrigin(Origins::BL);
	progressBar.SetPosition({ 0, FRAMEWORK.GetWindowSizeF().y });

	text1.setFont(FONT_MGR.Get("fonts/NotoSansKR-Medium.otf"));
	text1.setString(std::to_wstring(months) + L"번째 달 끝");
	text1.setCharacterSize(37);
	text1.setFillColor(sf::Color::Black);
	text1.setStyle(sf::Text::Bold);
	text1.setPosition(progressBar.GetGlobalBounds().left + 20.f, progressBar.GetGlobalBounds().top + 30.f);

	text2.setFont(FONT_MGR.Get("fonts/NotoSansKR-Medium.otf"));
	text2.setString(L"식사 시간");
	text2.setCharacterSize(32);
	text2.setFillColor(sf::Color::Black);
	text2.setStyle(sf::Text::Bold);
	text2.setPosition(text1.getGlobalBounds().left, text1.getGlobalBounds().top + text1.getGlobalBounds().height + 15.f);

	menuStr.setFont(FONT_MGR.Get("fonts/NotoSansKR-Medium.otf"));
	menuStr.setString(L"주민에게 음식 제공");
	menuStr.setCharacterSize(32);
	menuStr.setFillColor(sf::Color::Black);
	menuStr.setStyle(sf::Text::Bold);
	menuStr.setPosition({ text2.getGlobalBounds().left,
		text2.getGlobalBounds().top + text2.getGlobalBounds().height + 30.f });
	
	sf::FloatRect rect = menuStr.getGlobalBounds();
	backStr = sf::RectangleShape({ progressBar.GetGlobalBounds().width - 60.f, rect.height + 20.f });
	backStr.setPosition({ text2.getGlobalBounds().left - 10.f, rect.top - 13.f });
	backStr.setFillColor(sf::Color(255, 244, 206));

	lines.setFillColor(sf::Color::Black);
	lines.setSize({ menuStr.getGlobalBounds().width, 3.f });
	lines.setPosition(menuStr.getGlobalBounds().left, menuStr.getGlobalBounds().top + menuStr.getGlobalBounds().height + 5.f);
}

void UiSys::SetEndProgress()
{
	progressBar.Reset();
	progressBar.Set({ 9, 7 }, { 44.f, 44.f });
	progressBar.SetScale({ 1.f,1.f });
	progressBar.SetOrigin(Origins::MC);
	progressBar.SetPosition(FRAMEWORK.GetWindowCenterPos());

	text1.setString(L"GAME OVER");
	text1.setCharacterSize(50);
	text1.setPosition(progressBar.GetGlobalBounds().left + 20.f, progressBar.GetGlobalBounds().top + 30.f);

	text2.setString(std::to_wstring(months + 1) + L"번째 달에 도달했습니다.");
	text2.setCharacterSize(32);
	text2.setPosition(text1.getGlobalBounds().left, text1.getGlobalBounds().top + text1.getGlobalBounds().height + 15.f);

	menuStr.setString(L"메뉴로 돌아가기");
	menuStr.setCharacterSize(32);
	menuStr.setPosition({ text2.getGlobalBounds().left,
		text2.getGlobalBounds().top + text2.getGlobalBounds().height + 60.f });

	sf::FloatRect rect = menuStr.getGlobalBounds();
	backStr = sf::RectangleShape({ progressBar.GetGlobalBounds().width - 60.f, rect.height + 20.f });
	backStr.setPosition({ text2.getGlobalBounds().left - 10.f, rect.top - 13.f });
	backStr.setFillColor(sf::Color(255, 244, 206));
}
