#include "TestScene1.h"
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
    this->schedule(schedule_selector(TestScene1::addUnitL), 3);
    this->schedule(schedule_selector(TestScene1::addUnitR), 3);

    this->scheduleUpdate();

    return true;
}

#pragma region createUnit
//유닛 생성 함수 (스케줄 함수로 생성할 때 쓰임)
void TestScene1::createUnitL()
{
    Unit* unit = Unit::createUnitL();
    unitsL.pushBack(unit);

    this->addChild(unit);
    unit->moveUnit();
}

void TestScene1::createUnitR()
{
    Unit* unit = Unit::createUnitR();
    unitsR.pushBack(unit);

    this->addChild(unit);
    unit->moveUnit();
}
#pragma endregion

#pragma region init
void TestScene1::initData()
{
    unitsL.clear();
    unitsR.clear();
}
#pragma endregion

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
                //적 유닛일 때
                if (u1->myFactory != u2->myFactory)
                {
                    log("unit1 unit2 collision");

                    //log("%f", u1->getHp());
                    //log("%f", u2->getHp());

                    u1->enemy = u2;
                    u2->enemy = u1;

                    if (u1->time > u1->delay)
                        u1->attack();

                    if (u2->time > u2->delay)
                        u2->attack();

                        //u2->stopAction(u2->move);
                        //u2->schedule(schedule_selector(Unit::scheduleAttack, 2.0f));
                        //u2->stopUnit();
                        //u2->schedule(schedule_selector(Unit::actionAttack), 2.0f);


                    /*
                    if (u1->getHp() <= 0)
                    {
                        removeUnit(u1);
                    }
                    if (u2->getHp() <= 0)
                    {
                        removeUnit(u2);
                    }
                    */
                }
            }
            else
            {
            }
            /*else
            {
                u1->enemy = nullptr;
                u2->enemy = nullptr;

                u1->unschedule(schedule_selector(Unit::hit, 2.0f));
                u2->unschedule(schedule_selector(Unit::hit, 2.0f));
            }*/
        }
    }
    
}

/*
void TestScene1::removeUnit(Ref* pSender)
{
    auto u = (Unit*)pSender;

    if (u->getMyFac() == facL)
    {
        //unitsL.eraseObject(u);
        u->unschedule(schedule_selector(Unit::actionAttack));
    }
    else
    {
        //unitsR.eraseObject(u);
        u->schedule(schedule_selector(Unit::actionAttack));
    }
    
    this->removeChild(u);

}
*/
#pragma region schedule fuunction
void TestScene1::addUnitL(float f)
{
    createUnitL();
}

void TestScene1::addUnitR(float f)
{
    createUnitR();
}
#pragma endregion