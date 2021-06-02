#pragma
#include "cocos2d.h"
using namespace cocos2d;

class TestScene1 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(TestScene1);
};