#pragma once
#include "mecro.h"


class GameManager
{
#pragma region singleton
	static GameManager* m_hThis;
	
public:
	static GameManager* GetInstance()
	{
		if (m_hThis == nullptr)
			m_hThis = new GameManager;

		return m_hThis;
	}

#pragma endregion

private:
	bool isRightFactory_Die = false;
	bool isLeftFactory_Die = false;
	bool isBac = true;
public:
	void Die_Right_Factory();
	void Die_Left_Factory();
	void Reset();

	bool Return_isRightFactory_Die() { return isRightFactory_Die; };
	bool Return_isLeftFactory_Die() { return isLeftFactory_Die; };

	void Play_Bac();

	int frontUnitLeft = 0; //���� �տ� �ִ� ���� ����
	int frontUnitRight = 0; //���� �տ� �ִ� ������ ����
	int totalUnitNumL = 0; //�� ���� ����
	int totalUnitNumR = 0; //�� ���� ����
	void initUnitNum(); //�� ���� �ʱ�ȭ

	void diedUnitL();
	void diedUnitR();
};