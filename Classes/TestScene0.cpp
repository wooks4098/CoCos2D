#include "TestScene0.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

//모든 유닛 저장
Vector<Unit*> unitsL;
Vector<Unit*> unitsR;

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

	unitsL.clear();
	unitsR.clear();

	Create_BackGround();
	Creat_Factory();

	//팩토리 스케줄 등록
	this->schedule(schedule_selector(TestScene0::Factory_Right_CreatUnitCheck), 1);
	this->schedule(schedule_selector(TestScene0::Factory_Left_CreatUnitCheck), 1);
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
	for(int i = 0; i<7; i++)
	{
		factory[FACTORY_RIGHT].return_Factory_Sp()->addChild(factory[FACTORY_RIGHT].return_Circle_bubble(i));
		factory[FACTORY_RIGHT].return_Factory_Sp()->addChild(factory[FACTORY_RIGHT].return_Rhombus_bubble(i));
		factory[FACTORY_LEFT].return_Factory_Sp()->addChild(factory[FACTORY_LEFT].return_Circle_bubble(i));
		factory[FACTORY_LEFT].return_Factory_Sp()->addChild(factory[FACTORY_LEFT].return_Rhombus_bubble(i));
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

	UI_Left_bottom_Info = Sprite::create("UI/UI_bottom_Info_Left.png");
	UI_Left_bottom_Info->setAnchorPoint(Vec2(0, 0));
	UI_Left_bottom_Info->setPosition(0, 0);
	this->addChild(UI_Left_bottom_Info);

	UI_Left_bottom_Inven = Sprite::create("UI/UI_bottom_Inventory.png");
	UI_Left_bottom_Inven->setAnchorPoint(Vec2(0, 0));
	UI_Left_bottom_Inven->setPosition(UI_Left_bottom_Info->getContentSize().width, 0);
	this->addChild(UI_Left_bottom_Inven);
	
	UI_Left_bottom_Delet = Sprite::create("UI/UI_bottom_Delet.png");
	UI_Left_bottom_Delet->setAnchorPoint(Vec2(0, 0));
	UI_Left_bottom_Delet->setPosition(UI_Left_bottom_Inven->getContentSize().width, 0);
	this->addChild(UI_Left_bottom_Delet);
	
	UI_Right_bottom_Info = Sprite::create("UI/UI_bottom_Info_Right.png");
	UI_Right_bottom_Info->setAnchorPoint(Vec2(1, 0));
	UI_Right_bottom_Info->setPosition(winSize.width,0);
	this->addChild(UI_Right_bottom_Info);

	UI_Right_bottom_Inven = Sprite::create("UI/UI_bottom_Inventory.png");
	UI_Right_bottom_Inven->setAnchorPoint(Vec2(1, 0));
	UI_Right_bottom_Inven->setPosition(winSize.width - UI_Right_bottom_Info->getContentSize().width, 0);
	this->addChild(UI_Right_bottom_Inven);

	UI_Right_bottom_Delet = Sprite::create("UI/UI_bottom_Delet.png");
	UI_Right_bottom_Delet->setAnchorPoint(Vec2(1, 0));
	UI_Right_bottom_Delet->setPosition(winSize.width - UI_Right_bottom_Inven->getContentSize().width,0 );
	this->addChild(UI_Right_bottom_Delet);


}
void TestScene0::Update(float f)
{

}

void TestScene0::Factory_Right_CreatUnitCheck(float f)
{
	//factory[FACTORY_RIGHT].CreatUnit();
	//if (!test1)
	{
		CreatUnitR();
		test1 = !test1;
	}
}

void TestScene0::Factory_Left_CreatUnitCheck(float f)
{
	//factory[FACTORY_LEFT].CreatUnit();
	//if (!test0)
	{
		CreatUnitL();
		test0 = !test0;
	}
}

void TestScene0::CreatUnitL()
{
	Unit* unit = LeftUnit::createUnitL(&factory[FACTORY_LEFT], &factory[FACTORY_RIGHT]);
	unit->initUnit();
	unitsL.pushBack(unit);
	this->addChild(unit);
	unit->moveUnit();
	//this->unschedule(schedule_selector(TestScene1::addUnitL)); //실험용
}

void TestScene0::CreatUnitR()
{
	Unit* unit = RightUnit::createUnitR(&factory[FACTORY_RIGHT], &factory[FACTORY_LEFT]);
	unit->initUnit();
	unitsR.pushBack(unit);
	this->addChild(unit);
	unit->moveUnit();

	//this->unschedule(schedule_selector(TestScene1::addUnitR)); //실험용
}
