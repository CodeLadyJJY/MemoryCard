#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "GameDefine.h"
#include "Card.h"

class GameScene : public cocos2d::Layer
{
private:
	int cardNum;							//卡片总数
	int reverseNum;							//翻转的卡片总数
	int map[cardRowNum][cardRowNum];		//卡片地图
	bool isJudging;							//是否正在判断图片相同中
	Card* allCards[cardRowNum][cardRowNum];	//所有背景卡片
	Card* reverseCards[2];					//翻转的卡牌

public:
	void clickCard(int x, int y);
	void JudgeSame(float t);				//判断两张卡片是否相同
	void cleanCard(Card * sp);				//相同则清除卡片
	void recoverBG(Card * sp);				//不相同则恢复背景
	void addNewGameButton();

	static cocos2d::Scene * createScene();
	virtual bool init();
	void menuCallBack(cocos2d::Ref* obj);
	CREATE_FUNC(GameScene);
};

#endif