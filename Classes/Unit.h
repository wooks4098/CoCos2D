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

	//HP��
	Sprite* emptyHP;
	Sprite* fullHP;


	//�Լ�
	void initUnit(); //���� �ʱ�ȭ
	void initUnitL(); //���� �ʱ�ȭ
	void initUnitR(); //���� �ʱ�ȭ

	void virtual moveUnit() = 0; //���� �̵�
	void virtual attackUnit(Unit* enemy) = 0; //�� ���� �����ϱ�
	void damaged(float damage); //�������� �Դ� �Լ�
	void virtual dieUnit() = 0; //���� ���

	//�ݹ� �Լ�
	void virtual callbackAttack(Unit* enemy) { }

	//������ �Լ�
	void virtual update(float f) = 0;
};

class LeftUnit :public Unit
{
public:
	static Unit* createUnitL(); //���� ����

	void moveUnit() override; //���� �̵�
	void attackUnit(Unit* enemy) override; //������ �����ϱ�
	void dieUnit() override; //���� ���
	void update(float f) override;

	//�ݹ� �Լ�
	void callbackAttack(Unit* enemy) override; //attackUnit���� ȣ���ϴ� �Լ�
};

class RightUnit :public Unit
{
public:
	static Unit* createUnitR(); //���� ����

	//������ �Լ�
	void moveUnit() override; //���� �̵�
	void attackUnit(Unit* enemy) override; //������ �����ϱ�
	void dieUnit() override; //���� ���
	void update(float f) override;

	//�ݹ� �Լ�
	void callbackAttack(Unit* enemy) override; //attackUnit���� ȣ���ϴ� �Լ�
};