#pragma once
#include <Unit.h>

class RightUnit :public Unit
{
public:
	static Unit* createUnit(Factory* myFac, Factory* enemyFac, BUBBLE bubble); //���� ����
	void initUnit(BUBBLE bubble) override; //���� �ʱ�ȭ

	void idleUnit() override; //���� ���
	void moveUnit() override; //���� �̵�
	void attackUnit(Unit* enemy) override; //�� ���� ����
	void attackFactory() override; //�� ���丮 ����
	void damaged(float damage) override; //������ �Դ� �Լ�
	void dieUnit() override; //���� ���
	void removeUnit() override; //���� ����
	void removeVector() override; //���Ϳ� �ִ� ���� ����

	void callbackAttack(Unit* enemy) override; //attackUnit���� ȣ��
	void callbackAttackFac() override; //attackFactory���� ȣ��

	//������ �Լ�
	void update(float f) override; //���� �浹 üũ
};