#pragma once
#include "cocos2d.h"
#include <string>
#include "Bubble.h"
#include "GameManager.h"
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
	float CreatUnit_timeCheck;	//���� ���� ��Ÿ�� üũ
	float CreatUnit_time;		//���� ���� ��Ÿ��
	float CreatUnit_time_Base = 30;	//���� ���� ��Ÿ�� �ʱⰪ

	BUBBLE Circle_bubble;
	BUBBLE Rhombus_bubble;

	Sprite* Hp_Bar;
	Sprite* Hp_Bar_Back;
	Sprite* Factory_sp;
	Menu *menu;

	Sprite* Circle_bubble_sprite[8];
	Sprite* Rhombus_bubble_sprite[8];


public:
	Factory();

	//Creat
	void Create(int factoryNumber);//���丮 ���� �Լ�
	void CreatUnit(); //���� ���� �Լ�
	void Change_CreatUnit_Time(float time); //���� ���� ��Ÿ�� ���� �Լ�

	void Factory_Hp_Down();//���丮 Hp ����
	void Factory_Damage_Action();//���丮 ������ �׼�
	void Factory_Hit_Check(Sprite* _unit);//���丮 �浹 üũ

	void Change_Bubble(BUBBLE _Bubble);	//���� ����
	void SetPos_Bubble();
	void Change_Bubble_Setting(BUBBLE _Bubble);//���� ���� �� ���丮 ü�� �����ӵ� ����

	//Sprite creat
	void Create_HpBar();
	void Create_Factory_Sp();
	void Create_Bubble();
	//Menu Creat
	void Create_HpDownMenu();

	void Test();
	int Change_Key(int _key);



	//Scene�� ��Ͻ�Ű�� ���� ����
	Sprite* return_HpBar() { return Hp_Bar; };
	Sprite* return_HpBar_Back() { return Hp_Bar_Back; };
	Sprite* return_Factory_Sp() { return Factory_sp; };

	Menu* return_Menu() { return menu; };

	Sprite* return_Circle_bubble(int number) { return Circle_bubble_sprite[number]; };
	Sprite* return_Rhombus_bubble(int number) { return Rhombus_bubble_sprite[number]; };

	//�ݹ� �Լ�
	void HpDown(Ref* Sender);

	

};

