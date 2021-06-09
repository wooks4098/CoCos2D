#ifndef __SceneTrans__GameScene
#define __SceneTrans__GameScene


#include "Factory.h"
#include "mecro.h"
#include "GameManager.h"
#include "Unit.h"
#include "LeftUnit.h"
#include "RightUnit.h"

#include "cocos2d.h"
using namespace cocos2d;

class GameScene : public cocos2d::Scene
{
private:
	Size winSize;
	Factory factory[2];

	//Sprite
	Sprite* UI_Hp_top;
	Sprite* Factory_Back;
	Sprite* end_Image;
	//menu
	Menu *End_menu;
	bool isEndOpen = false;
	//Bubble UI
	Sprite* UI_Left_bottom_Info;
	MenuItemImage* UI_Left_bottom_Bubble;
	MenuItemImage* UI_Left_bottom_Unit;
	Sprite* UI_Left_bottom_Inven;
	Sprite* UI_Left_bottom_Delet;

	Sprite* UI_Right_bottom_Info;
	MenuItemImage* UI_Right_bottom_Bubble;
	MenuItemImage* UI_Right_bottom_Unit;
	Sprite* UI_Right_bottom_Inven;
	Sprite* UI_Right_bottom_Delet;

	Label* Lcoin;
	Label* Rcoin;
	Label* Lbitcoincost;
	Label* Rbitcoincost;

	//dimu
	INVENPOS invenPos_Left[8];
	INVENPOS invenPos_Right[8];
	int lCount;
	int RCount;
	std::vector<Bubble*> bubblesLeft1;
	std::vector<Bubble*> bubblesRight2;
	cocos2d::Vector<Bubble*> bubblesLeft;
	cocos2d::Vector<Bubble*> bubblesRight;
	cocos2d::Vector<Bubble*> bubblesTest;
	int bitCoinL;
	int bubbleCostL;
	int bitCoinR;
	int bubbleCostR;
	static bool isMove;
	
	int coinAmount;
	BUBBLE val;
	int randnum;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();    
    CREATE_FUNC(GameScene);

	void Creat_Factory();
	void Create_BackGround();
	void Creat_End_Menu(bool isRightWin);

	BUBBLE GetPP(int lev);
	void ClickToCreateBubble1(Ref* pSender, int lev, bool isRight);
	void initData() { bubblesLeft.clear(); bubblesRight.clear(); }

	//스케줄
	void Factory_Right_CreatUnitCheck(float f);	//팩토리(Right) 유닛 생성 체크
	void Factory_Left_CreatUnitCheck(float f);	//팩토리(Left) 유닛 생성 체크
	void Update(float f);//업데이트
	void OneTwoThreeFourBubbleBubbleRight(float f);
	void OneTwoThreeFourBubbleBubbleLeft(float f);
	//void OneTwoThreeFourBubbleBubbleTest(float f);
	void GetCoinInTime(float f);

	//콜백
	void go_Play(Ref* pSender);
	void go_Menu(Ref* pSender);
};

#endif // _SceneTrans__GameScene
