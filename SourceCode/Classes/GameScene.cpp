#include "GameScene.h"
#include "GameDefine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene * GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if(!Layer::init())
		return false;

	//初始化
	cardNum = cardRowNum * cardRowNum;
	reverseNum = 0;
	isJudging = false;

	for (int i = 0; i < cardRowNum; i++)
	{
		for (int j = 0; j < cardRowNum; j++)
		{
			map[i][j] = 0;
		}
	}
	
	//随机分配图片
	srand(time(NULL));

	for (int i = 0; i < cardRowNum; i++)
	{
		for (int j = 0; j < cardRowNum; j++)
		{
			if (map[i][j] == 0)
			{
				map[i][j] = rand() % cardRowNum + 1;
				auto sp1 = Card::create(map[i][j]);
				sp1->setPositionRC(i, j);
				this->addChild(sp1);
				allCards[i][j] = sp1;

				while (1)
				{
					int r = rand() % cardRowNum;
					int c = rand() % cardRowNum;
					if (map[r][c] == 0)
					{
						map[r][c] = map[i][j];
						auto sp2 = Card::create(map[r][c]);
						sp2->setPositionRC(r, c);
						this->addChild(sp2);
						allCards[r][c] = sp2;
						break;
					}
				}
			}
		}
	}

	//触摸侦听
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&](Touch * t, Event * e){
		int x = t->getLocation().x / cardWidth;
		int y = t->getLocation().y / cardHeight;

		if (map[x][y] && !isJudging)
		{
			if (reverseNum == 0)
			{
				clickCard(x, y);
				reverseNum = 1;
			}
			else if (reverseNum == 1 && (x != reverseCards[0]->getX() || y != reverseCards[0]->getY()))
			{
				clickCard(x, y);
				reverseNum = 0;
				isJudging = true;
				this->scheduleOnce(schedule_selector(GameScene::JudgeSame), 0.3f);
			}
		}
		
		return true;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void GameScene::clickCard(int x, int y)
{
	auto sp = allCards[x][y];
	sp->showCard();
	reverseCards[reverseNum] = sp;
}

void GameScene::JudgeSame(float t)
{
	int x1 = reverseCards[0]->getX();
	int y1 = reverseCards[0]->getY();
	int x2 = reverseCards[1]->getX();
	int y2 = reverseCards[1]->getY();
	if (map[x1][y1] == map[x2][y2])
	{
		cleanCard(reverseCards[0]);
		cleanCard(reverseCards[1]);
	}
	else
	{
		recoverBG(reverseCards[0]);
		recoverBG(reverseCards[1]);
	}

	isJudging = false;

	//游戏结束
	if (cardNum == 0)
	{
		this->addNewGameButton();
	}
}

void GameScene::cleanCard(Card * sp)
{
	int x = sp->getX();
	int y = sp->getY();
	sp->removeFromParent();
	map[x][y] = 0;
	cardNum--;
}

void GameScene::recoverBG(Card * sp)
{
	sp->recoverBG();
}

void GameScene::addNewGameButton()
{
	//添加新游戏按钮
	auto menuItemNew = MenuItemFont::create("New Game", CC_CALLBACK_1(GameScene::menuCallBack, this));
	auto menu = Menu::create(menuItemNew, NULL);

	menu->setPosition(Point::ZERO);
	menuItemNew->setPosition(Point(winSize_width / 2, winSize_height / 2));
	//menuItemNew->setColor(Color3B(0, 0, 0));

	this->addChild(menu);
}

void GameScene::menuCallBack(Ref* obj)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}