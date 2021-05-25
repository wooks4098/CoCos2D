#ifndef __SceneTrans__GameScene
#define __SceneTrans__GameScene

#include "cocos2d.h"
#include "Factory.h"
#include "mecro.h"
using namespace cocos2d;

class GameScene : public cocos2d::Scene
{
private:
	Size winSize;
	Factory factory[2];

	//Sprite
	Sprite* UI_Hp_top;
	Sprite* Factory_Back;

	//dimu
	std::vector<Bubble*> bubblesLeft;
	std::vector<Bubble*> bubblesRight;
	BUBBLE val;
	int randnum;

	int bitCoin;
	int count;
	static bool isMove;

	Bubble* bubbleA;
	Bubble* bubbleB;
	Sprite* DeleteZoneL;
	Sprite* DeleteZoneR;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();    
    CREATE_FUNC(GameScene);

	void Creat_Factory();
	void Create_BackGround();

	BUBBLE GetPP(int lev);
	void ClickToCreateBubble1(Ref* pSender, int lev, bool isRight);

	//������
	void Factory_Right_CreatUnitCheck(float f);	//���丮(Right) ���� ���� üũ
	void Factory_Left_CreatUnitCheck(float f);	//���丮(Left) ���� ���� üũ
	void Update(float f);//������Ʈ
	void OneTwoThreeFourBubbleBubbleRight(float f);
	void OneTwoThreeFourBubbleBubbleLeft(float f);
};

#endif // _SceneTrans__GameScene
