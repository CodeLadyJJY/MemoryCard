#ifndef _CARD_H_
#define _CARD_H_

#include "cocos2d.h"

class Card : public cocos2d::Sprite
{
private:
	int x, y;
	cocos2d::Sprite* bg;
	cocos2d::Sprite* card;

public:
	void setPositionRC(int x, int y);
	void showCard();	//œ‘ æÕº∆¨
	void recoverBG();	//ª÷∏¥±≥æ∞Õº∆¨
	int getX();
	int getY();

	static Card* create(int type);
	virtual bool init(int type);
};

#endif
