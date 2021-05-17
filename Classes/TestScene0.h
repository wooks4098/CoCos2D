#ifndef __SceneTrans__TestScene0
#define __SceneTrans__TestScene0

#include "cocos2d.h"
#include "Factory.h"
using namespace cocos2d;
class TestScene0 : public cocos2d::Scene
{
private: 
	Size winSize;
	Factory factory;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TestScene0);

	//void HpDown(Ref* Sender);
}; 

#endif // !__SceneTrans__TestScene0
