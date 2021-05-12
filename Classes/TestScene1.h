#ifndef __SceneTrans__TestScene1
#define __SceneTrans__TestScene1

#include "cocos2d.h"

class TestScene1 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TestScene1);

	
};

#endif // !__SceneTrans__TestScene1
