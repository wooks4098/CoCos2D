#include "GameManager.h"
#include "SoundManager.h"
GameManager* GameManager::m_hThis = nullptr;


void GameManager::Die_Right_Factory()
{
	isRightFactory_Die = true;

}
void GameManager::Die_Left_Factory()
{
	isLeftFactory_Die = true;
}

void GameManager::Reset()
{
	isRightFactory_Die = false;
	isLeftFactory_Die = false;
}

void GameManager::Play_Bac()
{
	if (isBac)
	{
		SoundManager::GetInstance()->Play(BackGround_0);

		isBac = false;
	}
}

void GameManager::diedUnitL()
{
	frontUnitLeft++;
}

void GameManager::diedUnitR()
{
	frontUnitRight++;
}

void GameManager::initUnitNum()
{
	frontUnitLeft = 0; //제일 앞에 있는 왼쪽 유닛
	frontUnitRight = 0; //제일 앞에 있는 오른쪽 유닛
	totalUnitNumL = 0; //총 유닛 개수
	totalUnitNumR = 0; //총 유닛 개수
}