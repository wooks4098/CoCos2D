#include "HelloWorldScene.h"
#include "MenuScene .h"
using namespace cocos2d;

Scene* MenuScene::createScene()
{
	return MenuScene::create();
}

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto wlayer = LayerColor::create(Color4B(255, 255, 255, 180));
	addChild(wlayer);
}