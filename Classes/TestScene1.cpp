#include "TestScene1.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

Scene* TestScene1::createScene()
{
    return TestScene1::create();
}

bool TestScene1::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto wlayer = LayerColor::create(Color4B::GRAY);
    this->addChild(wlayer);
    
    //유닛 생성
    createUnit1();
    createUnit2();

    //유닛 충돌 체크
    this->schedule(schedule_selector(TestScene1::collisionUnit1));
    this->schedule(schedule_selector(TestScene1::collisionUnit2));


    return true;
}

//유닛 생성
void TestScene1::createUnit1()
{
 	//팩토리 위치로 수정하기
    Size winSize = Director::getInstance()->getWinSize();
	Vec2 factory1 = Vec2(0, winSize.height / 2);
    Vec2 factory2 = Vec2(winSize.width, winSize.height / 2);

    unit1 = Sprite::create("CyanSquare.png");
    unit1->setPosition(factory1);
    this->addChild(unit1);

    //유닛 이동
    moveUnit1 = MoveTo::create(3, factory2); //상대 팩토리로 이동
    unit1->runAction(moveUnit1); //액션 실행
}

void TestScene1::createUnit2()
{
    //팩토리 위치로 수정하기
    Size winSize = Director::getInstance()->getWinSize();
    Vec2 factory1 = Vec2(0, winSize.height / 2);
    Vec2 factory2 = Vec2(winSize.width, winSize.height / 2);

    unit2 = Sprite::create("YellowSquare.png");
    unit2->setPosition(factory2);
    this->addChild(unit2);

    //유닛 이동
    moveUnit2 = MoveTo::create(3, factory1); //상대 팩토리로 이동
    unit2->runAction(moveUnit2); //액션 실행
}

void TestScene1::collisionUnit1(float f)
{
    if (unit1 == nullptr)
    {
        log("unit1 is null!");
        this->createUnit1();

        return;
    }

    if (unit1->getBoundingBox().intersectsRect(unit2->getBoundingBox()))
    {
        log("unit1 unit2 collision");

        fightUnit();
    }
}

void TestScene1::collisionUnit2(float f)
{
    if (unit2 == nullptr)
    {
        log("unit2 is null!");
        this->createUnit2();

        return;
    }

    if (unit2->getBoundingBox().intersectsRect(unit1->getBoundingBox()))
    {
        log("unit2 unit1 collision");

        fightUnit();
    }
}

void TestScene1::fightUnit()
{
    this->stopAction(moveUnit1);
    this->stopAction(moveUnit2);

    if (num < 300)
    {
        log("unit fight!!! - %d", num);
        num++;
    }
    else
    {
        log("unit die!!!");
        num = 0;

        unit1->removeFromParentAndCleanup(true);
        unit1 = nullptr;
        this->removeChild(unit1);

        unit2->removeFromParentAndCleanup(true);
        unit2 = nullptr;
        this->removeChild(unit2);

    }


}