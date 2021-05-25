#ifndef __SceneTrans__TestScene2
#define __SceneTrans__TestScene2

#include "cocos2d.h"
#include "Bubble.h"
#include "time.h"

class TestScene2 : public cocos2d::Scene
{
private:
	std::vector<Bubble*> bubblesLeft;
	std::vector<Bubble*> bubblesRight;
	BUBBLE val;
	int randnum;


public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	int count;
	static bool isMove;

	Bubble* bubbleA;
	Bubble* bubbleB;

	//Sprite* DeleteZoneL;
	//Sprite* DeleteZoneR;
	BUBBLE GetPP(int lev);
	void ClickToCreateBubble1(Ref* pSender,int lev, bool isRight);
	void Click2(Ref* pSender);
	void myTick(float f);

	CREATE_FUNC(TestScene2);

	
};

#endif // !__SceneTrans__TestScene2
