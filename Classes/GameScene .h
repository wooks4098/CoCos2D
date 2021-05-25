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

	//스케줄
	void Factory_Right_CreatUnitCheck(float f);	//팩토리(Right) 유닛 생성 체크
	void Factory_Left_CreatUnitCheck(float f);	//팩토리(Left) 유닛 생성 체크
	void Update(float f);//업데이트
	void OneTwoThreeFourBubbleBubbleRight(float f);
	void OneTwoThreeFourBubbleBubbleLeft(float f);
};

#endif // _SceneTrans__GameScene
