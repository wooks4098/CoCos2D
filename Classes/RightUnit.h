#pragma once
#include <Unit.h>

class RightUnit :public Unit
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
	void update(float f) override; //���� �浹 üũ

	//�ݹ� �Լ�
	void callbackAttack(Unit* enemy) override; //attackUnit���� ȣ���ϴ� �Լ�
	void callbackAttackFac() override; //������ �� ȣ��
	void removeUnitFromVector() override; //dieUnit���� ȣ���ϴ� �ݹ� �Լ�
};