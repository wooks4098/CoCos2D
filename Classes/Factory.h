#pragma once
#include "cocos2d.h"
#include <string>
using namespace cocos2d; 


class Factory : public cocos2d::Sprite
{
private:
	Size winSize;

	int MaxHp;		//�ִ� ü��
	int CurHp;		//���� ü��
	bool isRight;	//������ �����ʿ� �ִ���

	Sprite* Hp_Bar;
	Sprite* Hp_Bar_Back;
	Menu *menu;

public:
	Factory();

	//HP��
	void Create_HpBar();
	Sprite* return_HpBar() { return Hp_Bar; };
	Sprite* return_HpBar_Back() { return Hp_Bar_Back; };
	//�޴�
	void Create_HpDownMenu();
	Menu* return_Menu() { return menu; };


	//�ݹ� �Լ�
	void HpDown(Ref* Sender);

};

