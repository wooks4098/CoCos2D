#include "Unit.h"

//초기화
void Unit::initData()
{
	myFactoryPos = Vec2(myFactory->return_Factory_Sp()->getPosition().x, myFactory->return_Factory_Sp()->getPosition().y - 50);
	enemyFactoryPos = Vec2(enemyFactory->return_Factory_Sp()->getPosition().x, enemyFactory->return_Factory_Sp()->getPosition().y - 50);

	this->setPosition(this->myFactoryPos);

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