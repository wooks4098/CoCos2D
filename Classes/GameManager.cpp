#include "GameManager.h"
GameManager* GameManager::m_hThis = nullptr;


bool GameManager::Die_Right_Factory()
{
	isRightFactory_Die = true;
}
bool GameManager::Die_Left_Factory()
{
	isLeftFactory_Die = true;
}