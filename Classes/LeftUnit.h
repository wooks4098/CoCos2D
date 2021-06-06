#pragma once
#include <Unit.h>

class LeftUnit :public Unit
{
public:
	static Unit* createUnit(Factory* myFac, Factory* enemyFac); //���� ����
	void initUnit() override; //���� �ʱ�ȭ

	void idleUnit() override; //���� ���
	void moveUnit() override; //���� �̵�
	void attackUnit(Unit* enemy) override; //������ �����ϱ�
	void attackFactory() override; //�� ���� �����ϱ�
	void damaged(float damage) override; //������ �Դ� �Լ�
	void dieUnit() override; //���� ���
	void removeUnit() override; //���� ����

	//�ݹ� �Լ�
	void callbackAttack(Unit* enemy) override; //attackUnit���� ȣ���ϴ� �ݹ� �Լ�
	void callbackAttackFac() override; //������ �� ȣ��

	//������ �Լ�
	void update(float f) override; //���� �浹 üũ
};
