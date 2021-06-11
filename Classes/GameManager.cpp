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
	if(isBac)
		SoundManager::GetInstance()->Play(BackGround_0);
}

void GameManager::diedUnitL()
{
	forwardUnitLeft++;
}

void GameManager::diedUnitR()
{
	forwardUnitRight++;
}