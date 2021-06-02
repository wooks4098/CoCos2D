#include "TestScene1.h"
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

    return true;
}

