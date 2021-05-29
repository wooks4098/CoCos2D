#include "Unit.h"
#include "TestScene1.h"

#pragma region create&init unit
Unit* Unit::createUnitL()
{
	//���������� Unit�� �������� ���� ��� ���α׷��� ���� �ʵ��� ����ó��
	Unit* sprite = new (std::nothrow)Unit();

	const char* fileName;

	fileName = "Character/C/CMove_0.png";
	sprite->myFactory = TestScene1::getInstance()->facL;
	sprite->enemyFactory = TestScene1::getInstance()->facR;

	sprite->maxHp = 50;
	sprite->hp = 50;
	sprite->speed = 200;
	sprite->power = 5;
	
	sprite->initUnit();
	sprite->initAni();
	sprite->scheduleUpdate();

	if (sprite && sprite->initWithFile(fileName))
	{
		sprite->autorelease(); //��������Ʈ ����� ���� �� �ڵ����� �޸𸮿��� ���ŵ� �� �ֵ���
		return sprite;
	}

	CC_SAFE_DELETE(sprite); //����� ���� ��������Ʈ ����
	return nullptr;
}

Unit* Unit::createUnitR()
{
	//���������� Unit�� �������� ���� ��� ���α׷��� ���� �ʵ��� ����ó��
	Unit* sprite = new (std::nothrow)Unit();

	const char* fileName;

	fileName = "Character/A/AMove_0.png";
	sprite->myFactory = TestScene1::getInstance()->facR;
	sprite->enemyFactory = TestScene1::getInstance()->facL;

	sprite->maxHp = 20;
	sprite->hp = 20;
	sprite->speed = 100;
	sprite->power = 2;

	sprite->initUnit();
	sprite->initAni();

	sprite->scheduleUpdate();

	if (sprite && sprite->initWithFile(fileName))
	{
		sprite->autorelease(); //��������Ʈ ����� ���� �� �ڵ����� �޸𸮿��� ���ŵ� �� �ֵ���
		return sprite;
	}

	CC_SAFE_DELETE(sprite); //����� ���� ��������Ʈ ����
	return nullptr;
}

#pragma endregion

#pragma region init
//���� �ʱ�ȭ
void Unit::initUnit()
{
	Size unitSize = this->getContentSize(); //�� ������ �ȵǳ�
	this->setPosition(this->myFactory);
	/*
	//hp��
	emptyHP = Sprite::create("Character/emptyHP.png");
	fullHP = Sprite::create("Character/fullHP.png");

	emptyHP->setPosition(Vec2(unitSize.width + 150, unitSize.height + 300));
	fullHP->setPosition(Vec2(unitSize.width + 150, unitSize.height + 300));

	this->addChild(emptyHP, 3);
	this->addChild(fullHP, 4);
	*/
}

//�ִϸ��̼� �ʱ�ȭ
void Unit::initAni()
{
	if (this->enemyFactory == TestScene1::getInstance()->facL)
	{
		//�̵� �ִϸ��̼�
		moveAni = Animation::create();
		moveAni->setDelayPerUnit(0.3f);

		moveAni->addSpriteFrameWithFile("Character/A/AMove_0.png");
		moveAni->addSpriteFrameWithFile("Character/A/AMove_1.png");
		moveAni->addSpriteFrameWithFile("Character/A/AMove_2.png");
		moveAni->addSpriteFrameWithFile("Character/A/AMove_3.png");
		moveAni->addSpriteFrameWithFile("Character/A/AMove_4.png");
		moveAni->addSpriteFrameWithFile("Character/A/AMove_5.png");

		moveAct = Animate::create(moveAni);

		//���� �ִϸ��̼�
		attackAni = Animation::create();
		attackAni->setDelayPerUnit(0.3f);

		attackAni->addSpriteFrameWithFile("Character/A/AAttack_0.png");
		attackAni->addSpriteFrameWithFile("Character/A/AAttack_1.png");
		attackAni->addSpriteFrameWithFile("Character/A/AAttack_2.png");
		attackAni->addSpriteFrameWithFile("Character/A/AAttack_3.png");
		attackAni->addSpriteFrameWithFile("Character/A/AAttack_4.png");
		attackAni->addSpriteFrameWithFile("Character/A/AAttack_5.png");

		attackAct = Animate::create(attackAni);

		//��� �ִϸ��̼�
		dieAni = Animation::create();
		dieAni->setDelayPerUnit(0.3f);

		dieAni->addSpriteFrameWithFile("Character/A/ADeath_0.png");
		dieAni->addSpriteFrameWithFile("Character/A/ADeath_1.png");
		dieAni->addSpriteFrameWithFile("Character/A/ADeath_2.png");
		dieAni->addSpriteFrameWithFile("Character/A/ADeath_3.png");
		dieAni->addSpriteFrameWithFile("Character/A/ADeath_4.png");
		dieAni->addSpriteFrameWithFile("Character/A/ADeath_5.png");
		dieAni->addSpriteFrameWithFile("Character/A/ADeath_6.png");
		dieAni->addSpriteFrameWithFile("Character/A/ADeath_7.png");
		dieAni->addSpriteFrameWithFile("Character/A/ADeath_8.png");
		dieAni->addSpriteFrameWithFile("Character/A/ADeath_9.png");
		dieAni->addSpriteFrameWithFile("Character/A/ADeath_10.png");
		dieAni->addSpriteFrameWithFile("Character/A/ADeath_11.png");

		dieAct = Animate::create(dieAni);
	}
	else
	{
		//�̵� �ִϸ��̼�
		moveAni = Animation::create();
		moveAni->setDelayPerUnit(0.3f);

		moveAni->addSpriteFrameWithFile("Character/C/CMove_0.png");
		moveAni->addSpriteFrameWithFile("Character/C/CMove_1.png");
		moveAni->addSpriteFrameWithFile("Character/C/CMove_2.png");
		moveAni->addSpriteFrameWithFile("Character/C/CMove_3.png");
		moveAni->addSpriteFrameWithFile("Character/C/CMove_4.png");
		moveAni->addSpriteFrameWithFile("Character/C/CMove_5.png");

		moveAct = Animate::create(moveAni);

		//���� �ִϸ��̼�
		attackAni = Animation::create();
		attackAni->setDelayPerUnit(0.3f);

		attackAni->addSpriteFrameWithFile("Character/C/CAttack_0.png");
		attackAni->addSpriteFrameWithFile("Character/C/CAttack_1.png");
		attackAni->addSpriteFrameWithFile("Character/C/CAttack_2.png");
		attackAni->addSpriteFrameWithFile("Character/C/CAttack_3.png");
		attackAni->addSpriteFrameWithFile("Character/C/CAttack_4.png");
		attackAni->addSpriteFrameWithFile("Character/C/CAttack_5.png");

		attackAct = Animate::create(attackAni);

		//��� �ִϸ��̼�
		dieAni = Animation::create();
		dieAni->setDelayPerUnit(0.3f);

		dieAni->addSpriteFrameWithFile("Character/C/CDeath_0.png");
		dieAni->addSpriteFrameWithFile("Character/C/CDeath_1.png");
		dieAni->addSpriteFrameWithFile("Character/C/CDeath_2.png");
		dieAni->addSpriteFrameWithFile("Character/C/CDeath_3.png");
		dieAni->addSpriteFrameWithFile("Character/C/CDeath_4.png");
		dieAni->addSpriteFrameWithFile("Character/C/CDeath_5.png");
		dieAni->addSpriteFrameWithFile("Character/C/CDeath_6.png");
		dieAni->addSpriteFrameWithFile("Character/C/CDeath_7.png");
		dieAni->addSpriteFrameWithFile("Character/C/CDeath_8.png");
		dieAni->addSpriteFrameWithFile("Character/C/CDeath_9.png");
		dieAni->addSpriteFrameWithFile("Character/C/CDeath_10.png");
		dieAni->addSpriteFrameWithFile("Character/C/CDeath_11.png");

		dieAct = Animate::create(dieAni);
	}
}
#pragma endregion

#pragma region animation & action
//�̵� �׼�, �ִϸ��̼�
void Unit::moveUnit()
{
	float distance = fabs(enemyFactory.x - this->getPosition().x);
	move = MoveTo::create(distance / this->speed, enemyFactory);
	this->runAction(move);

	auto moveRep = RepeatForever::create(moveAct);
	this->runAction(moveRep);
}
#pragma endregion

/*
#pragma region animation
 void Unit::actionMove(float f)
 {
	 rep = RepeatForever::create(moveAct);
	 this->runAction(rep);
 }
 void Unit::actionAttack(float f)
 {
	 rep = RepeatForever::create(attackAct);
	 this->runAction(rep);
 }
 void Unit::actionDie(float f)
 {
	 rep = RepeatForever::create(dieAct);
	 this->runAction(rep);
 }
#pragma endregion

#pragma region action
 //�̵�



//���� ���� ��
void Unit::damaged()
{
	hp -= enemy->power;

	if (hp <= 0)
	{
		die();
	}
}

//��� ó��
void Unit::die()
{
	log("\n\ndie\n\n");
}
#pragma endregion
*/
#pragma region schedule function
void Unit::attack()
{
	this->stopAction(move);
	this->runAction(attackAct);

	//this->schedule(schedule_selector(Unit::scheduleAttack, 1));
}

/*
//�浹 üũ
void Unit::update(float f)
{
	fullHP->setTextureRect(Rect(0, 0, fullHP->getContentSize().width * hp / maxHp, fullHP->getContentSize().height));
}
*/
#pragma endregion

