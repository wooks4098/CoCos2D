#pragma once
#include "cocos2d.h"
#include <string>
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

	Sprite* Hp_Bar;
	Sprite* Hp_Bar_Back;
	Menu *menu;

public:
	Factory();

	void Create(int factoryNumber);//팩토리 생성 함수
	void CreatUnit(float f); //유닛 생성 함수
	void Change_CreatUnit_Time(float time); //유닛 생성 쿨타임 변경 함수
	



	//HP바
	void Create_HpBar();
	Sprite* return_HpBar() { return Hp_Bar; };
	Sprite* return_HpBar_Back() { return Hp_Bar_Back; };
	//메뉴
	void Create_HpDownMenu();
	Menu* return_Menu() { return menu; };


	//콜백 함수
	void HpDown(Ref* Sender);

	

};

