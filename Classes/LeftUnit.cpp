#include "LeftUnit.h"

extern Vector<Unit*> unitsL;
extern Vector<Unit*> unitsR;

#pragma region create
Unit* LeftUnit::createUnit(Factory* myFac, Factory* enemyFac)
{
	//���������� Unit�� �������� ���� ��� ���α׷��� ���� �ʵ��� ����ó��
	Unit* sprite = new (std::nothrow)LeftUnit();

	const char* fileName;

	fileName = "Character/C/CMove_0.png";

	sprite->myFactory = myFac;
	sprite->enemyFactory = enemyFac;

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
#pragma endregion

#pragma region init
void LeftUnit::initUnit()
{
	initData();
	
	maxHp = 50;
	hp = maxHp;
	speed = 300;
	power = 10;

	fullHP->setScaleX(0.5); //���� ��...
}
#pragma endregion

#pragma region action & animation
void LeftUnit::idleUnit()
{
	this->stopAllActions();
	isFighting = false;

	auto idleAni = Animation::create();
	idleAni->setDelayPerUnit(0.3f);
	idleAni->addSpriteFrameWithFile("Character/C/CMove_0.png");
	auto rep = Repeat::create(Animate::create(idleAni), -1);
	this->runAction(rep);
}

void LeftUnit::moveUnit()
{
	this->stopAllActions();
	isFighting = false;

	float distance = fabs(enemyFactory->return_Factory_Sp()->getPosition().x - getPosition().x);
	auto move = MoveTo::create(distance / speed, enemyFactory->return_Factory_Sp()->getPosition());

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

	auto spawn = Spawn::create(Repeat::create(animate, -1), move, nullptr);
	this->runAction(spawn);
}

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
	auto seq = Sequence::create(Animate::create(attackAni), CallFunc::create(CC_CALLBACK_0(LeftUnit::callbackAttack, this, enemy)), DelayTime::create(1.5f), nullptr); //�ִϸ��̼�+����, ������ ����������
	auto rep = Repeat::create(seq, -1); //�ִϸ��̼�, ����, ������
	this->runAction(rep);
}

void LeftUnit::attackFactory()
{
	this->stopAllActions();
	isFighting = true;

	//Right ���� �ִϸ��̼�
	auto attackAni = Animation::create();
	attackAni->setDelayPerUnit(0.3f);
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_0.png");
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_1.png");
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_2.png");
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_3.png");
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_4.png");
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_5.png");

	auto seq = Sequence::create(Animate::create(attackAni), CallFunc::create(CC_CALLBACK_0(LeftUnit::callbackAttackFac, this)), DelayTime::create(1.5f), nullptr); //�ִϸ��̼�+����, ������ ����������
	auto rep = Repeat::create(seq, -1); //�ִϸ��̼�, ����, ������
	this->runAction(rep);
}


void LeftUnit::dieUnit()
{
	this->stopAllActions();
	isDieAct = true;

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
	
	auto removeFromVector = CallFunc::create(CC_CALLBACK_0(LeftUnit::removeUnitFromVector, this));
	auto remove = CallFunc::create(CC_CALLBACK_0(Unit::removeUnit, this));
	//auto hpBarFadeOut = CallFunc::create(CC_CALLBACK_0(Unit::hpBarfadeOut, this));

	auto seq = Sequence::create(animate, removeFromVector, remove, nullptr);
	this->runAction(seq);
}
#pragma endregion

#pragma region callback function
void LeftUnit::callbackAttack(Unit* enemy)
{
	enemy->damaged(power);
	if (enemy->isDied)
	{
		moveUnit();
	}
}

void LeftUnit::callbackAttackFac()
{
	enemyFactory->Factory_Hp_Down();
}

//���� �޴� �Լ�
void LeftUnit::damaged(float damage)
{
	hp -= damage;

	if (hp <= 0)
	{
		hp = 0;
		isDied = true;
		if(!isDieAct)
			this->dieUnit();
	}
}

void LeftUnit::removeUnitFromVector()
{
	if (unitsL.contains(this))
		unitsL.eraseObject(this);
	else
		unitsR.eraseObject(this);
}
#pragma endregion

#pragma region schedule functio
void LeftUnit::update(float f)
{
	Rect myRect = getBoundingBox();
	Rect enemyFacRect = enemyFactory->return_Factory_Sp()->getBoundingBox();


	for (Unit* e : unitsR)
	{
		Rect enemyRect = e->getBoundingBox();

		//������ �浹�� ��
		if (myRect.intersectsRect(enemyRect) && !e->isDied)
		{
			if (!isFighting)
				attackUnit(e);
		}
	}

	//������ �浹���� ���� �� (�켱 ���� = �� > �� ���丮) �����ؾ���
	if (myRect.intersectsRect(enemyFacRect))
	{
		//���丮 ����
		log("Attack the enemy factory");
		if (!isFighting)
			attackFactory();
	}

	//�Ʊ��� �浹�� ��
	for (Unit* b : unitsL)
	{
		Rect buddyRect = b->getBoundingBox();

		if (myRect.intersectsRect(buddyRect))
		{
			//���ֺ��� �浹�� �Ʊ� ������ �� ����� ���丮�� ����� ��
			if (myRect.origin.x < buddyRect.origin.x && isStop == false)
			{
				isStop = true;
				buddyUnit = b;
				idleUnit();
			}
		}
		else
		{
			if (b == buddyUnit)
			{
				isStop = false;
				buddyUnit = nullptr;
				moveUnit();
			}
		}
	}
}
#pragma endregion