
#include "HelloWorldScene.h"
#include "GameScene .h"

using namespace cocos2d;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto wlayer = LayerColor::create(Color4B(255, 255, 255, 255));
	addChild(wlayer);
}