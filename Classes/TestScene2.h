#ifndef __SceneTrans__TestScene2
#define __SceneTrans__TestScene2

#include "cocos2d.h"
#include "Bubble.h"

class TestScene2 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	int count;

	Bubble* bubbleA;
	Bubble* bubbleB;
	Bubble* bubbleC;

	void CreateBubble2();
	void ClickToCreateBubble1(Ref* pSender);
	void Click2(Ref* pSender);
	void myTick(float f);

	CREATE_FUNC(TestScene2);

	
};

#endif // !__SceneTrans__TestScene2

