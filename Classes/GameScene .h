#ifndef __SceneTrans__GameScene
#define __SceneTrans__GameScene

#include "cocos2d.h"
#include "Factory.h"
#include "mecro.h"
using namespace cocos2d;

class GameScene : public cocos2d::Scene
{
private:
	Size winSize;
	Factory factory[2];

	//Sprite
	Sprite* UI_Hp_top;
	Sprite* Factory_Back;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();    
    CREATE_FUNC(GameScene);

	void Creat_Factory();
	void Create_BackGround();

	//스케줄
	void Factory_Right_CreatUnitCheck(float f);	//팩토리(Right) 유닛 생성 체크
	void Factory_Left_CreatUnitCheck(float f);	//팩토리(Left) 유닛 생성 체크
	void Update(float f);//업데이트
};

#endif // _SceneTrans__GameScene
