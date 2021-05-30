#pragma once
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#endif

#include "cocos2d.h"

using namespace cocos2d;

class TestScene1;

class Unit : public cocos2d::Sprite
{
public:
	//�������ͽ�
	float maxHp; //�ִ� ü��
	float hp; //���� ü��
	float speed; //�̵��ӵ�
	float power; //��

	bool isFighting = false; //�ο�� ������
	bool isDied = false; //�׾�����
	
	
	//���丮 ����
	Vec2 myFactory;
	Vec2 enemyFactory;

	//������ ���
	Unit* enemy;

	//HP��
	Sprite* emptyHP;
	Sprite* fullHP;


	//�Լ�
	void initUnit(); //���� �ʱ�ȭ
	void initUnitL(); //���� �ʱ�ȭ
	void initUnitR(); //���� �ʱ�ȭ

	void virtual moveUnit() = 0; //���� �̵�
	void virtual attackUnit() = 0; //�� ���� �����ϱ�
	void damaged(float damage); //�������� �Դ� �Լ�
	void virtual dieUnit() = 0; //���� ���

	//�ݹ� �Լ�
	void virtual callbackAttack() { }

	//������ �Լ�
	void update(float f) override;
};

class LeftUnit :public Unit
{
public:
	static Unit* createUnitL(); //���� ����

	void moveUnit() override; //���� �̵�
	void attackUnit() override; //������ �����ϱ�
	void dieUnit() override; //���� ���

	//�ݹ� �Լ�
	void callbackAttack() override; //attackUnit���� ȣ���ϴ� �Լ�
};

class RightUnit :public Unit
{
public:
	static Unit* createUnitR(); //���� ����

	//������ �Լ�
	void moveUnit() override; //���� �̵�
	void attackUnit() override; //������ �����ϱ�
	void dieUnit() override; //���� ���

	//�ݹ� �Լ�
	void callbackAttack() override; //attackUnit���� ȣ���ϴ� �Լ�
};