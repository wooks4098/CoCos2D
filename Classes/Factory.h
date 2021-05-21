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
	Sprite* Factory_sp;
	Menu *menu;
public:
	Factory();

	//Creat
	void Create(int factoryNumber);//���丮 ���� �Լ�
	void CreatUnit(); //���� ���� �Լ�
	void Change_CreatUnit_Time(float time); //���� ���� ��Ÿ�� ���� �Լ�

	void Factory_Hp_Down();//���丮 Hp ����
	void Factory_Damage_Action();//���丮 ������ �׼�
	void Factory_Hit_Check(Sprite* _unit);//���丮 �浹 üũ

	//Sprite creat
	void Create_HpBar();
	void Create_Factory_Sp();
	//Menu Creat
	void Create_HpDownMenu();




	//Scene�� ��Ͻ�Ű�� ���� ����
	Sprite* return_HpBar() { return Hp_Bar; };
	Sprite* return_HpBar_Back() { return Hp_Bar_Back; };
	Sprite* return_Factory_Sp() { return Factory_sp; };
	Menu* return_Menu() { return menu; };

	//�ݹ� �Լ�
	void HpDown(Ref* Sender);

	

};

