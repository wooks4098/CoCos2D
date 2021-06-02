#include "Unit.h"

//초기화
void Unit::initData()
{
	this->setPosition(this->myFactory->return_Factory_Sp()->getPosition());

	//hp바
	emptyHP = Sprite::create("Character/emptyHP.png");
	fullHP = Sprite::create("Character/fullHP.png");

	emptyHP->setPosition(Vec2(0, 300));
	fullHP->setPosition(Vec2(0, 300));

	emptyHP->setAnchorPoint(Vec2(0, 0));
	fullHP->setAnchorPoint(Vec2(0, 0));

	this->addChild(emptyHP, 3);
	this->addChild(fullHP, 4);
}

//공격 받는 함수
void Unit::damaged(float damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
		isDied = true;
		removeUnit();
	}
}

//제거하는 함수
void Unit::removeUnit()
{
	//애니메이션 추가
	auto removeSelf = RemoveSelf::create(true);
	this->runAction(removeSelf);
}
