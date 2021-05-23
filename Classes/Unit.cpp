#include "Unit.h"
#include "TestScene1.h"

#pragma region create&init unit
Unit* Unit::createUnit(Vec2 v)
{
	//정상적으로 Unit이 생성되지 않은 경우 프로그램이 죽지 않도록 예외처리
	Unit* sprite = new (std::nothrow)Unit();

	const char* fileName;

	if (v == TestScene1::getInstance()->facL)
	{
		fileName = "Unit1.png";
		sprite->myFactory = TestScene1::getInstance()->facL;
		sprite->enemyFactory = TestScene1::getInstance()->facR;
		sprite->setName("left unit");

		sprite->hp = 50;
		sprite->speed = 10;
		sprite->power = 5;
	}
	else
	{
		fileName = "Unit2.png";
		sprite->myFactory = TestScene1::getInstance()->facR;
		sprite->enemyFactory = TestScene1::getInstance()->facL;
		sprite->setName("right unit");

		sprite->hp = 20;
		sprite->speed = 5;
		sprite->power = 2;
	}
	
	sprite->setPosition(sprite->myFactory);

	if (sprite && sprite->initWithFile(fileName))
	{
		sprite->autorelease(); //스프라이트 사용이 끝날 때 자동으로 메모리에서 제거될 수 있도록
		return sprite;
	}

	CC_SAFE_DELETE(sprite); //사용이 끝난 스프라이트 제거
	return nullptr;
}
#pragma endregion

void Unit::moveUnit(float speed)
{
	float distance = fabs(enemyFactory.x - this->getPosition().x);
	move = MoveTo::create(distance / speed, enemyFactory);
	this->runAction(move);
}

void Unit::stopUnit()
{
	this->stopAction(move);
}

void Unit::collision(float f)
{

}

//공격 받을 때
void Unit::damaged()
{
	hp -= enemy->power;

	if (hp <= 0)
	{
		die();
	}
}

//공격할 때
void Unit::hit(float f)
{
	enemy->damaged();
}

void Unit::die()
{
	log("\n\ndie\n\n");
}