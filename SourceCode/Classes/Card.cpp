#include "Card.h"
#include "GameDefine.h"

USING_NS_CC;

Card* Card::create(int type)
{
	Card* pRet = new Card();
	if (pRet && pRet->init(type))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Card::init(int type)
{
	if (!Sprite::init())
	{
		return false;
	}

	//±³¾°Í¼Æ¬
	bg = Sprite::create("bg.jpeg");
	bg->setAnchorPoint(Point::ZERO);
	this->addChild(bg);

	//Ç°¾°Í¼Æ¬
	card = Sprite::create(StringUtils::format("%d.png", type));
	card->setAnchorPoint(Point::ZERO);
	this->addChild(card);
	card->setVisible(false);

	return true;
}

void Card::setPositionRC(int x, int y)
{
	this->x = x;
	this->y = y;
	this->setPosition(Vec2(x*cardWidth, y*cardHeight));
}

void Card::showCard()
{
	card->setVisible(true);
}

void Card::recoverBG()
{
	card->setVisible(false);
}

int Card::getX() { return this->x; }
int Card::getY() { return this->y; }