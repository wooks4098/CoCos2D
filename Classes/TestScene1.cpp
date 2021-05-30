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

#pragma region init
void TestScene1::initData()
{
    unitsL.clear();
    unitsR.clear();
}
#pragma endregion

#pragma region function
//유닛 제거
void TestScene1::removeUnit(Ref* pSender)
{
    auto ru = (Unit*)pSender;

    if (unitsL.contains((LeftUnit*)ru))
    {
        unitsL.eraseObject((LeftUnit*)ru);
    }
    else
    {
        unitsR.eraseObject((RightUnit*)ru);
    }
    
    this->removeChild(ru);
}
#pragma endregion

#pragma region schedule fuunction
void TestScene1::update(float f)
{
    Unit* remove;

    for (LeftUnit* u1 : unitsL)
    {
        if (u1->isDied)
        {
            remove = u1;
            //auto remove = Sequence::create(DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_1(TestScene1::removeChild, this, u1)), nullptr);
            //this->runAction(remove);
        }

        Rect rectU1 = u1->getBoundingBox();

        for (RightUnit* u2 : unitsR)
        {
            if (u2->isDied)
            {
                remove = u2;
            }

            Rect rectU2 = u2->getBoundingBox();

            //두 유닛이 충돌했을 때
            if (rectU1.intersectsRect(rectU2))
            {
                u1->enemy = u2;
                u2->enemy = u1;

                if (!u1->isFighting && u1->enemy != nullptr)
                    u1->attackUnit();

                if (!u2->isFighting && u2->enemy != nullptr)
                    u2->attackUnit();
            }
            else
            {
                u1->enemy = nullptr;
                u2->enemy = nullptr;
            }

        }

        removeUnit(remove);
    }

}

void TestScene1::addUnitL(float f)
{
    Unit* unit = LeftUnit::createUnitL();
    unit->initUnitL();
    unitsL.pushBack((LeftUnit*)unit);
    this->addChild(unit);
    unit->moveUnit();
    //this->unschedule(schedule_selector(TestScene1::addUnitL)); //실험용
}

void TestScene1::addUnitR(float f)
{
    Unit* unit = RightUnit::createUnitR();
    unit->initUnitR();
    unitsR.pushBack((RightUnit*)unit);
    this->addChild(unit);
    unit->moveUnit();
    //this->unschedule(schedule_selector(TestScene1::addUnitR)); //실험용
}
#pragma endregion