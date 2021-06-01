#include "GameManager.h"
GameManager* GameManager::m_hThis = nullptr;


void GameManager::Die_Right_Factory()
{
	isRightFactory_Die = true;
}
void GameManager::Die_Left_Factory()
{
	isLeftFactory_Die = true;
}