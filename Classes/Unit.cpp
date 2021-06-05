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
	
	this->addChild(emptyHP, 4);
	this->addChild(fullHP, 5);
}

//제거하는 함수
void Unit::removeUnit()
{
	auto removeSelf = RemoveSelf::create(true);
	this->runAction(removeSelf);
}