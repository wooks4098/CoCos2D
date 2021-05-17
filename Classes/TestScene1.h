#ifndef __SceneTrans__TestScene1
#define __SceneTrans__TestScene1

#include "cocos2d.h"

using namespace cocos2d;

class TestScene1 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TestScene1);


	Sprite* unit1;
	Sprite* unit2;
	int num;
	Action* moveUnit1;
	Action* moveUnit2;


	void createUnit1();
	void createUnit2();
	void collisionUnit1(float f);
	void collisionUnit2(float f);
	void fightUnit();
};

#endif // !__SceneTrans__TestScene1
