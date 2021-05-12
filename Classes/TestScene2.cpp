#include "TestScene2.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

Scene* TestScene2::createScene()
{
    return TestScene2::create();
}

bool TestScene2::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto wlayer = LayerColor::create(Color4B::BLUE);
    this->addChild(wlayer);
    return true;
}