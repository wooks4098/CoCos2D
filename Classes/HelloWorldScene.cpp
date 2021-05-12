#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "TestScene0.h"
#include "TestScene1.h"
#include "TestScene2.h"

#define W 0             //¿í·¡¾À   TestScene0
#define U 1             //ÁöÇö¾À   TestScene1
#define K 2             //Ã¤¿ø¾À   TestScene2


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

//////////////////////  ¾À »ý¼º [ÄÚµå °ª ³ÖÀ¸¼Å¿ä]  ////////////////////////////
//////#define W 0             //¿í·¡¾À   TestScene0
//////#define U 1             //ÁöÇö¾À   TestScene1
//////#define K 2             //Ã¤¿ø¾À   TestScene2

    switch (K)
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
    }
 

    return true;
}

//¾À »ý¼º 0 Á¶ / 1 À¯ / 2 ±è
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
