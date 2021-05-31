#include "mecro.h"

class GameManager
{
#pragma region ΩÃ±€≈Ê
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

public:
	bool Die_Right_Factory();
	bool Die_Left_Factory();


	bool Return_isRightFactory_Die() { return isRightFactory_Die; };
	bool Return_isLeftFactory_Die() { return isLeftFactory_Die; };



};