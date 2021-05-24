#pragma once
#include "cocos2d.h"
#include <string>
#include "Bubble.h"
#define FACTORY_RIGHT 0
#define FACTORY_LEFT 1
using namespace cocos2d; 

class Factory
{
private:
	Size winSize;

	int MaxHp;		//최대 체력
	int CurHp;		//현재 체력
	bool isRight;	//공장이 오른쪽에 있는지
	int CreatUnit_timeCheck;	//유닛 생성 쿨타임 체크
	int CreatUnit_time;		//유닛 생성 쿨타임

	BUBBLE Circle_bubble;
	BUBBLE Rhombus_bubble;

	Sprite* Hp_Bar;
	Sprite* Hp_Bar_Back;
	Sprite* Factory_sp;
	Menu *menu;

	Sprite* Circle_bubble_sprite[7];
	Sprite* Rhombus_bubble_sprite[7];


public:
	Factory();

	//Creat
	void Create(int factoryNumber);//팩토리 생성 함수
	void CreatUnit(); //유닛 생성 함수
	void Change_CreatUnit_Time(float time); //유닛 생성 쿨타임 변경 함수

	void Factory_Hp_Down();//팩토리 Hp 감소
	void Factory_Damage_Action();//팩토리 데미지 액션
	void Factory_Hit_Check(Sprite* _unit);//팩토리 충돌 체크

	void Change_Bubble(BUBBLE _Bubble);	//버블 변경

	void SetPos_Bubble();

	//Sprite creat
	void Create_HpBar();
	void Create_Factory_Sp();
	void Create_Bubble();
	//Menu Creat
	void Create_HpDownMenu();




	//Scene에 등록시키기 위한 리턴
	Sprite* return_HpBar() { return Hp_Bar; };
	Sprite* return_HpBar_Back() { return Hp_Bar_Back; };
	Sprite* return_Factory_Sp() { return Factory_sp; };

	Menu* return_Menu() { return menu; };

	Sprite* return_Circle_bubble() { return *Circle_bubble_sprite; };
	Sprite* return_Rhombus_bubble() { return *Rhombus_bubble_sprite; };

	//콜백 함수
	void HpDown(Ref* Sender);

	

};

