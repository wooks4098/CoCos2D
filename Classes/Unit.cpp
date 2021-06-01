#include "Unit.h"
#include "TestScene1.h"

extern Vector<Unit*> unitsL;
extern Vector<Unit*> unitsR;

#pragma region create&init unit
Unit* LeftUnit::createUnitL()
{
	//���������� Unit�� �������� ���� ��� ���α׷��� ���� �ʵ��� ����ó��
	Unit* sprite = new (std::nothrow)LeftUnit();

	const char* fileName;

	fileName = "Character/C/CMove_0.png";

	sprite->myFactory = TestScene1::getInstance()->facL;
	sprite->enemyFactory = TestScene1::getInstance()->facR;

	sprite->initUnit();

	sprite->scheduleUpdate();

	if (sprite && sprite->initWithFile(fileName))
	{
		sprite->autorelease(); //��������Ʈ ����� ���� �� �ڵ����� �޸𸮿��� ���ŵ� �� �ֵ���
		return sprite;
	}

	CC_SAFE_DELETE(sprite); //����� ���� ��������Ʈ ����
	return nullptr;
}

Unit* RightUnit::createUnitR()
{
	//���������� Unit�� �������� ���� ��� ���α׷��� ���� �ʵ��� ����ó��
	Unit* sprite = new (std::nothrow)RightUnit();

	const char* fileName;

	fileName = "Character/A/AMove_0.png";

	sprite->myFactory = TestScene1::getInstance()->facR;
	sprite->enemyFactory = TestScene1::getInstance()->facL;

	sprite->initUnit(); //���� �ʱ�ȭ

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
	Size unitSize = getContentSize(); //�� ������ �ȵǳ�
	this->setPosition(this->myFactory);
	
	//hp��
	emptyHP = Sprite::create("Character/emptyHP.png");
	fullHP = Sprite::create("Character/fullHP.png");

	emptyHP->setPosition(Vec2(0, unitSize.height + 300));
	fullHP->setPosition(Vec2(0, unitSize.height + 300));

	emptyHP->setAnchorPoint(Vec2(0, 0));
	fullHP->setAnchorPoint(Vec2(0, 0));

	this->addChild(emptyHP, 3);
	this->addChild(fullHP, 4);
}

void Unit::initUnitL()
{
	maxHp = 50;
	hp = maxHp;
	speed = 300;
	power = 10;
	log("Left HP : %d", hp);
}

void Unit::initUnitR()
{
	maxHp = 20;
	hp = maxHp;
	speed = 200;
	power = 2;
	log("Right HP : %d", hp);
}
#pragma endregion

#pragma region animation & action
//���
void LeftUnit::idleUnit()
{
	this->stopAllActions();

	auto idleAni = Animation::create();
	idleAni->addSpriteFrameWithFile("Character/C/CMove_0.png");
	auto animate = Animate::create(idleAni);
	this->runAction(animate);
}
void RightUnit::idleUnit()
{
	this->stopAllActions();

	auto idleAni = Animation::create();
	idleAni->addSpriteFrameWithFile("Character/A/AMove_0.png");
	auto animate = Animate::create(idleAni);
	this->runAction(animate);
}

//�̵�
void LeftUnit::moveUnit()
{
	this->stopAllActions();

	float distance = fabs(enemyFactory.x - getPosition().x);
	auto move = MoveTo::create(distance / speed, enemyFactory);

	//Right �̵� �ִϸ��̼�
	auto moveAni = Animation::create();
	moveAni->setDelayPerUnit(0.3f);
	moveAni->addSpriteFrameWithFile("Character/C/CMove_0.png");
	moveAni->addSpriteFrameWithFile("Character/C/CMove_1.png");
	moveAni->addSpriteFrameWithFile("Character/C/CMove_2.png");
	moveAni->addSpriteFrameWithFile("Character/C/CMove_3.png");
	moveAni->addSpriteFrameWithFile("Character/C/CMove_4.png");
	moveAni->addSpriteFrameWithFile("Character/C/CMove_5.png");
	auto animate = Animate::create(moveAni);

	auto spawn = Spawn::create(Repeat::create(animate,-1), move, nullptr);
	this->runAction(spawn);
}
void RightUnit::moveUnit()
{
	this->stopAllActions();

	float distance = fabs(enemyFactory.x - getPosition().x);
	auto move = MoveTo::create(distance / speed, enemyFactory);

	//Left �̵� �ִϸ��̼�
	auto moveAni = Animation::create();
	moveAni->setDelayPerUnit(0.3f);
	moveAni->addSpriteFrameWithFile("Character/A/AMove_0.png");
	moveAni->addSpriteFrameWithFile("Character/A/AMove_1.png");
	moveAni->addSpriteFrameWithFile("Character/A/AMove_2.png");
	moveAni->addSpriteFrameWithFile("Character/A/AMove_3.png");
	moveAni->addSpriteFrameWithFile("Character/A/AMove_4.png");
	moveAni->addSpriteFrameWithFile("Character/A/AMove_5.png");
	auto animate = Animate::create(moveAni);

	auto spawn = Spawn::create(Repeat::create(animate, -1), move, nullptr);
	this->runAction(spawn);
}

//����
void LeftUnit::attackUnit(Unit* enemy)
{
	this->stopAllActions();
	this->isFighting = true;

	//Right ���� �ִϸ��̼�
	auto attackAni = Animation::create();
	attackAni->setDelayPerUnit(0.3f);
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_0.png");
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_1.png");
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_2.png");
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_3.png");
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_4.png");
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_5.png");
	auto spawn = Spawn::create(Animate::create(attackAni), CallFunc::create(CC_CALLBACK_0(LeftUnit::callbackAttack, this, enemy)), nullptr); //�ִϸ��̼�, ���� ���ÿ�
	auto seq = Sequence::create(spawn, DelayTime::create(1.0f), nullptr); //�ִϸ��̼�+����, ������ ����������
	auto rep = Repeat::create(seq, -1); //�ִϸ��̼�, ����, ������
	this->runAction(rep);
}
void RightUnit::attackUnit(Unit* enemy)
{
	this->stopAllActions();
	this->isFighting = true;

	//Left���� �ִϸ��̼�
	auto attackAni = Animation::create();
	attackAni->setDelayPerUnit(0.3f);
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_0.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_1.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_2.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_3.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_4.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_5.png");
	auto spawn = Spawn::create(Animate::create(attackAni), CallFunc::create(CC_CALLBACK_0(RightUnit::callbackAttack, this, enemy)), nullptr); //�ִϸ��̼�, ���� ���ÿ�
	auto seq = Sequence::create(spawn, DelayTime::create(1.5f), nullptr); //�ִϸ��̼�+����, ������ ����������
	auto rep = Repeat::create(seq, -1); //�ִϸ��̼�, ����, ������
	this->runAction(rep);
}

//���
void LeftUnit::dieUnit()
{
	this->stopAllActions();
	isDied = true;

	auto dieAni = Animation::create();
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
	auto animate = Animate::create(dieAni);

	auto seq = Sequence::create(animate, DelayTime::create(2.0f), nullptr);
}
void RightUnit::dieUnit()
{
	this->stopAllActions();
	isDied = true;

	auto dieAni = Animation::create();
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
	auto animate = Animate::create(dieAni);

	auto seq = Sequence::create(animate, DelayTime::create(2.0f), nullptr);
}

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

#pragma region callback function
void LeftUnit::callbackAttack(Unit* enemy)
{
	enemy->damaged(power);
	if (enemy->isDied)
	{
		isFighting = false;
		moveUnit();
	}
}

void RightUnit::callbackAttack(Unit* enemy)
{
	enemy->damaged(power);
	if (enemy->isDied)
	{
		isFighting = false;
		moveUnit();
	}
}
#pragma endregion

#pragma region schedule function
void LeftUnit::update(float f)
{
	fullHP->setScaleX(hp / maxHp);

	Rect myRect = getBoundingBox();

	//������ �浹�� ��
	for (Unit* e : unitsR)
	{
		Rect enemyRect = e->getBoundingBox();

		if (myRect.intersectsRect(enemyRect))
		{
			if (!isFighting && !e->isDied)
				attackUnit(e);
		}
	}

	//�Ʊ��� �浹�� ��
	for (Unit* b : unitsL)
	{
		Rect buddyRect = b->getBoundingBox();

		if (myRect.intersectsRect(buddyRect))
		{
			//���ֺ��� �浹�� �Ʊ� ������ �� ����� ���丮�� ����� ��
			if (myRect.origin.x < buddyRect.origin.x)
			{
				idleUnit();
			}
		}
	}
}

void RightUnit::update(float f)
{
	fullHP->setScaleX(hp / maxHp);

	Rect myRect = getBoundingBox();

	//������ �浹�� ��
	for (Unit* e : unitsL)
	{
		Rect enemyRect = e->getBoundingBox();

		//�� ������ �浹���� ��
		if (myRect.intersectsRect(enemyRect))
		{
			if (!isFighting && !e->isDied)
				attackUnit(e);
		}
	}

	//�Ʊ��� �浹�� ��
	for (Unit* b : unitsR)
	{
		Rect buddyRect = b->getBoundingBox();

		if (myRect.intersectsRect(buddyRect))
		{
			//���ֺ��� �浹�� �Ʊ� ������ �� ����� ���丮�� ����� ��
			if (myRect.origin.x > buddyRect.origin.x)
			{
				idleUnit();
			}
		}
	}

}
#pragma endregion