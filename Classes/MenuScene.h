#ifndef __SceneTrans__MenuScene
#define __SceneTrans__MenuScene

#include "cocos2d.h"
using namespace cocos2d;

class MenuScene : public cocos2d::Scene
{
private:
	Size winSize;
	Sprite* Image;
	Menu *menu;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
 
    CREATE_FUNC(MenuScene);

	void CreatMenu();

	//ฤÝน้
	void Menu_Play(Ref* pSender);
	void Menu_Option(Ref* pSender);
	void Menu_Exit(Ref* pSender);

};
#endif // _SceneTrans__MenuScene


