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

	int MaxHp;		//�ִ� ü��
	int CurHp;		//���� ü��
	bool isRight;	//������ �����ʿ� �ִ���
	int CreatUnit_timeCheck;	//���� ���� ��Ÿ�� üũ
	int CreatUnit_time;		//���� ���� ��Ÿ��

	Sprite* Hp_Bar;
	Sprite* Hp_Bar_Back;
	Menu *menu;

public:
	Factory();

	void Create(int factoryNumber);//���丮 ���� �Լ�
	void CreatUnit(float f); //���� ���� �Լ�
	void Change_CreatUnit_Time(float time); //���� ���� ��Ÿ�� ���� �Լ�
	



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

