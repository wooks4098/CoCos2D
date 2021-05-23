#include "TestScene0.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

Scene* TestScene0::createScene()
{
	return TestScene0::create();
}

bool TestScene0::init()
{
    if (!Scene::init())
    {
        return false;
    }
	winSize = Director::getInstance()->getWinSize(); //화면의 사이즈 구하기

    auto wlayer = LayerColor::create(Color4B::WHITE);
    this->addChild(wlayer);

	Create_BackGround();
	Creat_Factory();

	//팩토리 스케줄 등록
	this->schedule(schedule_selector(TestScene0::Factory_Right_CreatUnitCheck), 0.1f);
	this->schedule(schedule_selector(TestScene0::Factory_Left_CreatUnitCheck), 0.1f);
	this->schedule(schedule_selector(TestScene0::Update));
    return true;
}

void TestScene0::Creat_Factory()
{
	//팩토리 생성
	factory[FACTORY_RIGHT].Create(FACTORY_RIGHT);

	factory[FACTORY_LEFT].Create(FACTORY_LEFT);
	//팩토리 등록
	this->addChild(factory[FACTORY_RIGHT].return_Menu());
	this->addChild(factory[FACTORY_RIGHT].return_HpBar_Back());
	this->addChild(factory[FACTORY_RIGHT].return_HpBar());
	this->addChild(factory[FACTORY_RIGHT].return_Factory_Sp());

	this->addChild(factory[FACTORY_LEFT].return_Menu());
	this->addChild(factory[FACTORY_LEFT].return_HpBar_Back());
	this->addChild(factory[FACTORY_LEFT].return_HpBar());
	this->addChild(factory[FACTORY_LEFT].return_Factory_Sp());
	//버블 등록
	//for (int i = 0; i < 7;)
	{
		factory[FACTORY_RIGHT].return_Factory_Sp()->addChild(factory[FACTORY_RIGHT].return_Circle_bubble());
		factory[FACTORY_RIGHT].return_Factory_Sp()->addChild(factory[FACTORY_RIGHT].return_Rhombus_bubble());
		factory[FACTORY_LEFT].return_Factory_Sp()->addChild(factory[FACTORY_LEFT].return_Circle_bubble());
		factory[FACTORY_LEFT].return_Factory_Sp()->addChild(factory[FACTORY_LEFT].return_Rhombus_bubble());
	}

}
void TestScene0::Create_BackGround()
{
	Factory_Back = Sprite::create("Factory/BG.png");
	Factory_Back->setAnchorPoint(Vec2(0, 0.5));
	Factory_Back->setPosition(0, winSize.height / 2);
	this->addChild(Factory_Back);

	UI_Hp_top = Sprite::create("UI/UI_top.png");
	UI_Hp_top->setAnchorPoint(Vec2(0, 1));
	UI_Hp_top->setPosition(0, winSize.height);
	this->addChild(UI_Hp_top);
}
void TestScene0::Update(float f)
{

}

void TestScene0::Factory_Right_CreatUnitCheck(float f)
{
	//factory[FACTORY_RIGHT].CreatUnit();
}

void TestScene0::Factory_Left_CreatUnitCheck(float f)
{
	//factory[FACTORY_LEFT].CreatUnit();
}