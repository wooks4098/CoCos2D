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
    auto wlayer = LayerColor::create(Color4B::YELLOW);
    this->addChild(wlayer);
    

    return true;
}