#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "GameDefine.h"
#include "Card.h"

class GameScene : public cocos2d::Layer
{
private:
	int cardNum;							//��Ƭ����
	int reverseNum;							//��ת�Ŀ�Ƭ����
	int map[cardRowNum][cardRowNum];		//��Ƭ��ͼ
	bool isJudging;							//�Ƿ������ж�ͼƬ��ͬ��
	Card* allCards[cardRowNum][cardRowNum];	//���б�����Ƭ
	Card* reverseCards[2];					//��ת�Ŀ���

public:
	void clickCard(int x, int y);
	void JudgeSame(float t);				//�ж����ſ�Ƭ�Ƿ���ͬ
	void cleanCard(Card * sp);				//��ͬ�������Ƭ
	void recoverBG(Card * sp);				//����ͬ��ָ�����
	void addNewGameButton();

	static cocos2d::Scene * createScene();
	virtual bool init();
	void menuCallBack(cocos2d::Ref* obj);
	CREATE_FUNC(GameScene);
};

#endif