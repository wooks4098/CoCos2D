#ifndef __SceneTrans__TestScene0
#define __SceneTrans__TestScene0

#include "cocos2d.h"
#include "Factory.h"

#define FACTORY_RIGHT 0
#define FACTORY_LEFT 1

using namespace cocos2d;
class TestScene0 : public cocos2d::Scene
{
private: 
	Size winSize;
	Factory factory[2];

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TestScene0);

	void ChangeBubble()
	{

	}


	//��ĳ��
	void Factory_Right_CreatUnitCheck(float f);	//���丮(Right) ���� ���� üũ
	void Factory_Left_CreatUnitCheck(float f);	//���丮(Left) ���� ���� üũ
};  

#endif // !__SceneTrans__TestScene0
