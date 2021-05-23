#include "TestScene1.h"
//#include "HelloWorldScene.h"
using namespace cocos2d;

#pragma region singleton
TestScene1* TestScene1::instance = NULL;
TestScene1* TestScene1::getInstance()
{
    if (instance == NULL)
        instance = new TestScene1;

    return instance;
}
#pragma endregion

#pragma region createScene
Scene* TestScene1::createScene()
{
    return TestScene1::create();
}
#pragma endregion

bool TestScene1::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto wlayer = LayerColor::create(Color4B::GRAY);
    this->addChild(wlayer);

    initData(); //데이터 초기화

    //유닛 생성
    createUnit(facL);
    createUnit(facR);

    this->scheduleUpdate();

    return true;
}

void TestScene1::createUnit(Vec2 v)
{
    Unit* unit = Unit::createUnit(v);
    if(v == facL)
        unitsL.pushBack(unit);
    else
        unitsR.pushBack(unit);

    this->addChild(unit);
    unit->moveUnit(300);

}

void TestScene1::initData()
{
    unitsL.clear();
    unitsR.clear();
}

void TestScene1::update(float f)
{
    for (Unit* u1 : unitsL)
    {
        Rect rectU1 = u1->getBoundingBox();
        for (Unit* u2 : unitsR)
        {
            Rect rectU2 = u2->getBoundingBox();
            
            //두 유닛이 충돌했을 때
            if (rectU1.intersectsRect(rectU2))
            {
                log("unit1 unit2 collision");

                log("%f", u1->getHp());
                log("%f", u2->getHp());

                u1->enemy = u2;
                u2->enemy = u1;

                //u1->hit(u2);
                u1->schedule(schedule_selector(Unit::hit, 2.0f));
                u1->stopUnit();

                //u2->hit(u1);
                u2->schedule(schedule_selector(Unit::hit, 2.0f));
                u2->stopUnit();

                if (u1->getHp() >= 0)
                    removeUnit(u1);
                if (u2->getHp() >= 0)
                    removeUnit(u2);
            }
            else
            {
                u1->enemy = nullptr;
                u2->enemy = nullptr;

                u1->unschedule(schedule_selector(Unit::hit, 2.0f));
                u2->unschedule(schedule_selector(Unit::hit, 2.0f));
            }
        }
    }
}

void TestScene1::removeUnit(Unit* u)
{
    if (u->getMyFac() == facL)
    {
        this->removeChild(u);
    }
    else
    {
        this->removeChild(u);
    }
}

//
//void TestScene1::fightUnit()
//{
//    this->stopAction(moveUnit1);
//    this->stopAction(moveUnit2);
//
//    if (num < 300)
//    {
//        log("unit fight!!! - %d", num);
//        num++;
//    }
//    else
//    {
//        log("unit die!!!");
//        num = 0;
//
//        unit1->removeFromParentAndCleanup(true);
//        unit1 = nullptr;
//        this->removeChild(unit1);
//
//        unit2->removeFromParentAndCleanup(true);
//        unit2 = nullptr;
//        this->removeChild(unit2);
//
//    }
//
//