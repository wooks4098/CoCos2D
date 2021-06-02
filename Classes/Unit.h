#pragma once
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#endif

#include "cocos2d.h"
#include "Factory.h"

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
	bool isStop = false; //�Ʊ� ���� �浹�� ���� �����ߴ���

	//�浹�� �Ʊ� ����
	Unit* buddyUnit = nullptr;

	//���丮 ����
	Factory* myFactory;
	Factory* enemyFactory;

	//HP��
	Sprite* emptyHP;
	Sprite* fullHP;


	//�Լ�
	void virtual initUnit()=0; //���� �ʱ�ȭ

	void virtual idleUnit() = 0; //���� ���
	void virtual moveUnit() = 0; //���� �̵�
	void virtual attackUnit(Unit* enemy) = 0; //�� ���� �����ϱ�
	void damaged(float damage); //�������� �Դ� �Լ�
	void virtual dieUnit() = 0; //���� ���

	//�ݹ� �Լ�
	void virtual callbackAttack(Unit* enemy) { }
	void removeUnit();

	//������ �Լ�
	void virtual update(float f) = 0;
};