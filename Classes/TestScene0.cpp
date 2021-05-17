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

	factory.Create_HpDownMenu();
	this->addChild(factory.return_Menu());
	
	factory.Create_HpBar();
	this->addChild(factory.return_HpBar_Back());
	this->addChild(factory.return_HpBar());


    return true;
}

//void TestScene0::HpDown(Ref* Sender)
//{
//
//}