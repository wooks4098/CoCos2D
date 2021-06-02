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
	void dieUnit() override; //���� ���
	void update(float f) override;

	//�ݹ� �Լ�
	void callbackAttack(Unit* enemy) override; //attackUnit���� ȣ���ϴ� �Լ�
};