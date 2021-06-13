#ifndef __SceneTrans__MainScene
#define __SceneTrans__MainScene
#pragma once


#include "mecro.h"



#include "cocos2d.h"
using namespace cocos2d;

class MainScene : public cocos2d::Scene
{
private:
	Size winSize;
	Sprite* Image;
	Menu *menu;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();    
    CREATE_FUNC(MainScene);
	void CreatMenu();

	//ฤÝน้
	void Menu_Play(Ref* pSender);
	void Menu_Exit(Ref* pSender);
};

#endif // _SceneTrans__GameScene
