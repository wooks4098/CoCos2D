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

    auto wlayer = LayerColor::create(Color4B::RED);
    this->addChild(wlayer);
 

    return true;
}

