#include "Unit.h"
#include "TestScene1.h"

#pragma region create&init unit
Unit* Unit::createUnit(Vec2 v)
{
	//���������� Unit�� �������� ���� ��� ���α׷��� ���� �ʵ��� ����ó��
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
		sprite->autorelease(); //��������Ʈ ����� ���� �� �ڵ����� �޸𸮿��� ���ŵ� �� �ֵ���
		return sprite;
	}

	CC_SAFE_DELETE(sprite); //����� ���� ��������Ʈ ����
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

//���� ���� ��
void Unit::damaged()
{
	hp -= enemy->power;

	if (hp <= 0)
	{
		die();
	}
}

//������ ��
void Unit::hit(float f)
{
	enemy->damaged();
}

void Unit::die()
{
	log("\n\ndie\n\n");
}