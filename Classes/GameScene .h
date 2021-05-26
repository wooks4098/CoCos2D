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
	std::vector<Bubble*> bubblesLeft;
	std::vector<Bubble*> bubblesRight;
	BUBBLE val;
	int randnum;
	int bitCoinL;
	int bubbleCostL;
	int bitCoinR;
	int bubbleCostR;
	static bool isMove;
	
	int coinAmount;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();    
    CREATE_FUNC(GameScene);

	void Creat_Factory();
	void Create_BackGround();

	BUBBLE GetPP(int lev);
	void ClickToCreateBubble1(Ref* pSender, int lev, bool isRight);

	//������
	void Factory_Right_CreatUnitCheck(float f);	//���丮(Right) ���� ���� üũ
	void Factory_Left_CreatUnitCheck(float f);	//���丮(Left) ���� ���� üũ
	void Update(float f);//������Ʈ
	void OneTwoThreeFourBubbleBubbleRight(float f);
	void OneTwoThreeFourBubbleBubbleLeft(float f);
	void GetCoinInTime(float f);
};

#endif // _SceneTrans__GameScene
