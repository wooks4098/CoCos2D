#ifndef __SceneTrans__TestScene0
#define __SceneTrans__TestScene0

#include "cocos2d.h"
#include "Factory.h"
#include "Unit.h"
#include "LeftUnit.h"
#include "RightUnit.h"

#define FACTORY_RIGHT 0
#define FACTORY_LEFT 1

using namespace cocos2d;
class TestScene0 : public cocos2d::Scene
{
private: 
	Size winSize;
	Factory factory[2];

	Sprite* UI_Hp_top;
	Sprite* Factory_Back;

	Sprite* UI_Left_bottom_Info;
	Sprite* UI_Left_bottom_Inven;
	Sprite* UI_Left_bottom_Delet;
	Sprite* UI_Right_bottom_Info;
	Sprite* UI_Right_bottom_Inven;
	Sprite* UI_Right_bottom_Delet;

	Menu* Bubble_Menu;

	bool test0 = false;
	bool test1 = false;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TestScene0);

	void ChangeBubble()
	{

	}

	void Creat_Factory();
	void Create_BackGround();
	void CreatUnitL();
	void CreatUnitR();

	//������
	void Factory_Right_CreatUnitCheck(float f);	//���丮(Right) ���� ���� üũ
	void Factory_Left_CreatUnitCheck(float f);	//���丮(Left) ���� ���� üũ
	void Update(float f);//������Ʈ
};  

#endif // !__SceneTrans__TestScene0
