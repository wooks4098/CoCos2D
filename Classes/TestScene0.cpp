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
	winSize = Director::getInstance()->getWinSize(); //ȭ���� ������ ���ϱ�

    auto wlayer = LayerColor::create(Color4B::WHITE);
    this->addChild(wlayer);

	//���丮 ����
	factory[FACTORY_RIGHT].Create(FACTORY_RIGHT);

	factory[FACTORY_LEFT].Create(FACTORY_LEFT);
	//���丮 ���
	this->addChild(factory[FACTORY_RIGHT].return_Menu());
	this->addChild(factory[FACTORY_RIGHT].return_HpBar_Back());
	this->addChild(factory[FACTORY_RIGHT].return_HpBar());

	this->addChild(factory[FACTORY_LEFT].return_Menu());
	this->addChild(factory[FACTORY_LEFT].return_HpBar_Back());
	this->addChild(factory[FACTORY_LEFT].return_HpBar());
	//���丮 ������ ���
	this->schedule(schedule_selector(TestScene0::Factory_Right_tick), 0.1f);
	this->schedule(schedule_selector(TestScene0::Factory_Left_tick), 0.1f);
    return true;
}

void TestScene0::Factory_Right_tick(float f)
{
	Right_Factory_UnitSpawntime += 0.1;
}

void TestScene0::Factory_Left_tick(float f)
{
	Left_Factory_UnitSpawntime += 0.1;
}