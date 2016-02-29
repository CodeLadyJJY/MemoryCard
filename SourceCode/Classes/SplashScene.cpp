#include "SplashScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene * SplashScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SplashScene::create();
	scene->addChild(layer);
	return scene;
}

bool SplashScene::init()
{
	if(!Layer::init())
		return false;

	auto size = Director::getInstance()->getWinSize();

	TTFConfig config("fonts/Marker Felt.ttf", 66);

	auto GameName = Label::createWithTTF(config, "Memory Card");
	GameName->setPosition(Vec2(size.width/2, size.height/2));
	this->addChild(GameName);

	auto GameAuthor = Label::createWithTTF(config, "GAME BY CodeLadyJJY");
	GameAuthor->setPosition(Vec2(size.width/2, size.height/3));
	GameAuthor->setScale(0.3);
	this->addChild(GameAuthor);

	this->scheduleOnce(schedule_selector(SplashScene::jumpToGame), 1.5);

	return true;
}

void SplashScene::jumpToGame(float t)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionProgressOutIn::create(1.5, scene));
}