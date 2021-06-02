#include "Unit.h"
#include "TestScene1.h"

#pragma region init


#pragma endregion

#pragma region function
//공격 받을 때
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

//제거할 때
void Unit::removeUnit()
{
	auto removeSelf = RemoveSelf::create(true);
	this->runAction(removeSelf);
}
#pragma endregion
