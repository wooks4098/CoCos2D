#include "Unit.h"
#include "TestScene1.h"

#pragma region init


#pragma endregion

#pragma region function
//���� ���� ��
void Unit::damaged(float damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
		//dieUnit();
		isDied = true;
		removeUnit();
	}
}

//������ ��
void Unit::removeUnit()
{
	auto removeSelf = RemoveSelf::create(true);
	this->runAction(removeSelf);
}
#pragma endregion
