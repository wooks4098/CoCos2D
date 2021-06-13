#include "HelloWorldScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameManager.h"
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
	winSize = Director::getInstance()->getWinSize(); //화면의 사이즈 구하기

	Image = Sprite::create("UI/Main/MUI_BG.png");
	Image->setAnchorPoint(Vec2(0, 0));
	Image->setPosition(0,0);
	this->addChild(Image);
	CreatMenu();
}

void MenuScene::CreatMenu()
{
	GameManager::GetInstance()->Play_Bac();
	auto _Play = cocos2d::MenuItemImage::create("UI/Main/MUI_SB0.png", "UI/Main/MUI_SB1.png", CC_CALLBACK_1(MenuScene::Menu_Play,this));
	_Play->setAnchorPoint(Vec2(0.5, 0.5));

	auto _Option = cocos2d::MenuItemImage::create("UI/Main/MUI_OB0.png", "UI/Main/MUI_OB1.png", CC_CALLBACK_1(MenuScene::Menu_Option, this));
	_Option->setAnchorPoint(Vec2(0.5, 0.5));
	_Option->setPosition(Vec2(0, -150));

	auto _Exit = cocos2d::MenuItemImage::create("UI/Main/MUI_EB0.png", "UI/Main/MUI_EB1.png", CC_CALLBACK_1(MenuScene::Menu_Exit, this));
	_Exit->setAnchorPoint(Vec2(0.5, 0.5));
	_Exit->setPosition(Vec2(0, -300));


	menu = Menu::create(_Play, _Option, _Exit,nullptr);
	menu->setPosition(Vec2(winSize.width/2, winSize.height/2));
	this->addChild(menu);
}

void MenuScene::Menu_Play(Ref* pSender)
{
	SoundManager::GetInstance()->Play(UI_Click);

	auto _GameScene = GameScene::createScene();
	Director::getInstance()->replaceScene(_GameScene);
}
void MenuScene::Menu_Option(Ref* pSender)
{

}
void MenuScene::Menu_Exit(Ref* pSender)
{
	SoundManager::GetInstance()->Play(UI_Click);
	Director::getInstance()->end();
}