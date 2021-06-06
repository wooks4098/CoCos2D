#pragma once
#include "cocos2d.h"
#include "Factory.h"
using namespace cocos2d;

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
	bool isStop = false; //�Ʊ� ���� �浹�� ���� ������ ��������
	bool isDieAct = false;
	bool isAttackFac = false;

	//�浹�� �Ʊ� ����
	Unit* buddyUnit = nullptr;

	//���丮 ����
	Factory* myFactory;
	Factory* enemyFactory;

	//HP��
	Sprite* emptyHP;
	Sprite* fullHP;

	//�Լ�
	void initData();
	void virtual initUnit() = 0; //���� �ʱ�ȭ
	void virtual idleUnit() = 0; //���� ���
	void virtual moveUnit() = 0; //���� �̵�
	void virtual attackUnit(Unit* enemy) = 0; //�� ���� �����ϱ�
	void virtual attackFactory() = 0; //�� ���� �����ϱ�
	void virtual dieUnit() = 0; //���� ���
	void virtual damaged(float damage) = 0; //������ �Դ� �Լ�

	//�ݹ� �Լ�
	void virtual callbackAttack(Unit* enemy) = 0; //������ �� ȣ��
	void virtual callbackAttackFac() = 0; //������ �� ȣ��
	void virtual removeUnit() = 0; //����� �� ȣ��

	//������ �Լ�
	void virtual update(float f) = 0;
};