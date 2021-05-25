#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "TestScene0.h"
#include "TestScene1.h"
#include "TestScene2.h"
#include "MenuScene .h"
#include "GameScene .h"

#define W 0             //����   TestScene0
#define U 1             //������   TestScene1
#define K 2             //ä����   TestScene2
#define Game 3
#define Menu 4

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


bool HelloWorld::init()
{
  
    if ( !Scene::init() )
    {
        return false;
    }

//////////////////////  �� ���� [�ڵ� �� �����ſ�]  ////////////////////////////
//////#define W 0             //����   TestScene0
//////#define U 1             //������   TestScene1
//////#define K 2             //ä����   TestScene2
//////#define Game 3          //���Ӿ�   GameScene
//////#define Menu 4          //�޴���   MenuScene

    switch (Game)
    {
    case 0:
        runAction(CallFuncN::create(CC_CALLBACK_1(HelloWorld::Scene0, this)));
        break;
    case 1:
        runAction(CallFuncN::create(CC_CALLBACK_1(HelloWorld::Scene1, this)));
        break;
    case 2:
        runAction(CallFuncN::create(CC_CALLBACK_1(HelloWorld::Scene2, this)));
        break;
	case 3:
		runAction(CallFuncN::create(CC_CALLBACK_1(HelloWorld::GameScene, this)));
		break;
	case 4:
		runAction(CallFuncN::create(CC_CALLBACK_1(HelloWorld::MenuScene, this)));
		break;
    }
 

    return true;
}

//�� ���� 0 �� / 1 �� / 2 ��
void HelloWorld::Scene0(Ref* pSender)
{
    auto pScene0 = TestScene0::createScene();
    Director::getInstance()->replaceScene(pScene0);
}
void HelloWorld::Scene1(Ref* pSender)
{
    auto pScene1 = TestScene1::createScene();
    Director::getInstance()->replaceScene(pScene1);
}
void HelloWorld::Scene2(Ref* pSender)
{
    auto pScene2 = TestScene2::createScene();
    Director::getInstance()->replaceScene(pScene2);
}
void HelloWorld::GameScene(Ref* pSender)
{
	auto GameScene = GameScene::createScene();
	Director::getInstance()->replaceScene(GameScene);
}
void HelloWorld::MenuScene(Ref* pSender)
{
	auto MenuScene = MenuScene::createScene();
	Director::getInstance()->replaceScene(MenuScene);
}