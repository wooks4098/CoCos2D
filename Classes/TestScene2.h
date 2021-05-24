#ifndef __SceneTrans__TestScene2
#define __SceneTrans__TestScene2

#include "cocos2d.h"
#include "Bubble.h"
#include "time.h"

class TestScene2 : public cocos2d::Scene
{
private:
	std::vector<Bubble*> bubbles;
	std::vector<int> bubbleis;
	BUBBLE val;
	//BUBBLE addval;
	int randnum;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	int count;
	static bool isMove;

	Bubble* bubbleA;
	Bubble* bubbleB;

	BUBBLE GetPP(int lev);
	void ClickToCreateBubble1(Ref* pSender,int lev);
	void Click2(Ref* pSender);
	void myTick(float f);

	CREATE_FUNC(TestScene2);

	
};

#endif // !__SceneTrans__TestScene2
