#include "TestScene1.h"
using namespace cocos2d;

//모든 유닛 저장
Vector<Unit*> unitsL;
Vector<Unit*> unitsR;

#pragma region singleton
TestScene1* TestScene1::instance = nullptr;
TestScene1* TestScene1::getInstance()
{
    if (instance == nullptr)
        instance = new TestScene1;

    return instance;
}

void TestScene1::releaseInstance()
{
    if (instance != NULL)
        delete instance;
}
#pragma endregion

TestScene1::TestScene1()
{
    unitsL.clear();
    unitsR.clear();
}

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

    //initData(); //데이터 초기화

    //유닛 생성
    this->schedule(schedule_selector(TestScene1::addUnitL), 5);
    this->schedule(schedule_selector(TestScene1::addUnitR), 5);

    this->scheduleUpdate();

    return true;
}

#pragma region init
void TestScene1::initData()
{
    unitsL.clear();
    unitsR.clear();
}
#pragma endregion

#pragma region function
//유닛 제거
void TestScene1::callbackRemove(Unit* unit)
{
    if (unitsL.contains(unit))
    {
        unitsL.eraseObject(unit);
    }
    else if(unitsR.contains(unit))
    {
        unitsR.eraseObject(unit);
    }
    
    this->removeChild(unit);
}
#pragma endregion

#pragma region schedule fuunction
void TestScene1::update(float f)
{

}

void TestScene1::addUnitL(float f)
{
    Unit* unit = LeftUnit::createUnitL();
    unit->initUnitL();
    unitsL.pushBack(unit);
    this->addChild(unit);
    unit->moveUnit();
    //this->unschedule(schedule_selector(TestScene1::addUnitL)); //실험용
}

void TestScene1::addUnitR(float f)
{
    Unit* unit = RightUnit::createUnitR();
    unit->initUnitR();
    unitsR.pushBack(unit);
    this->addChild(unit);
    unit->moveUnit();
    
    //this->unschedule(schedule_selector(TestScene1::addUnitR)); //실험용
}
#pragma endregion