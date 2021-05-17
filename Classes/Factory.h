#pragma once
#include "cocos2d.h"
#include <string>
using namespace cocos2d; 


class Factory : public cocos2d::Sprite
{
private:
	Size winSize;

	int MaxHp;		//최대 체력
	int CurHp;		//현재 체력
	bool isRight;	//공장이 오른쪽에 있는지

	Sprite* Hp_Bar;
	Sprite* Hp_Bar_Back;
	Menu *menu;

public:
	Factory();

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

