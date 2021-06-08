#include "LeftUnit.h"

extern Vector<Unit*> unitsL;
extern Vector<Unit*> unitsR;

#pragma region create
Unit* LeftUnit::createUnit(Factory* myFac, Factory* enemyFac, BUBBLE bubble)
{
	//���������� Unit�� �������� ���� ��� ���α׷��� ���� �ʵ��� ����ó��
	Unit* sprite = new (std::nothrow)LeftUnit();

	const char* fileName;

	fileName = "Character/C/CMove_0.png";

	sprite->myFactory = myFac;
	sprite->enemyFactory = enemyFac;

	sprite->initData();
	sprite->initUnit(bubble);

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
void LeftUnit::initUnit(BUBBLE bubble)
{
	//�����ؾ���
	if (bubble.Hp == 0)
		startHp = 50;
	else
		startHp = bubble.Hp;
	hp = startHp;

	if (bubble.MoveSpeed == 0)
		speed = 400;
	else
		//speed = bubble.MoveSpeed;
		speed = 300;

	if (bubble.Damage == 0)
		damage = 10;
	else
		//damage = bubble.Damage;
		damage = 10;
}
#pragma endregion


#pragma region remove
void LeftUnit::removeVector()
{
	if (unitsR.contains(this))
		unitsR.eraseObject(this);
}

//�����ϴ� �Լ�
void LeftUnit::removeUnit()
{
	if(unitsL.contains(this))
		unitsL.eraseObject(this);
	auto removeSelf = RemoveSelf::create(true);
	this->runAction(removeSelf);
}
#pragma endregion

#pragma region action & animation
void LeftUnit::idleUnit()
{
	this->stopAllActions();
	isFighting = false;
	isAttackFac = false;

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
	isAttackFac = false;

	float distance = fabs(enemyFactoryPos.x - myFactoryPos.x);
	auto move = MoveTo::create(distance / speed, enemyFactoryPos);

	//Left �̵� �ִϸ��̼�
	auto moveAni = Animation::create();
	moveAni->setDelayPerUnit(0.1f);
	moveAni->addSpriteFrameWithFile("Character/C/CMove_0.png");
	moveAni->addSpriteFrameWithFile("Character/C/CMove_1.png");
	moveAni->addSpriteFrameWithFile("Character/C/CMove_2.png");
	moveAni->addSpriteFrameWithFile("Character/C/CMove_3.png");
	moveAni->addSpriteFrameWithFile("Character/C/CMove_4.png");
	moveAni->addSpriteFrameWithFile("Character/C/CMove_5.png");
	auto animate = Animate::create(moveAni);
	auto rep = Repeat::create(animate, -1);
	
	this->runAction(move);
	this->runAction(rep);
}

void LeftUnit::attackUnit(Unit* enemy)
{
	this->stopAllActions();
	this->isFighting = true;
	isAttackFac = false;

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
	isAttackFac = true;

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

	auto remove = CallFunc::create(CC_CALLBACK_0(LeftUnit::removeUnit, this));
	auto removeV = CallFunc::create(CC_CALLBACK_0(LeftUnit::removeVector, this));
	auto seq = Sequence::create(removeV, animate, remove, nullptr);
	this->runAction(seq);

	auto fadeout = Spawn::create(DelayTime::create(2.4f), FadeOut::create(1.2f), nullptr);
	emptyHP->runAction(fadeout);
}
#pragma endregion

#pragma region callback function
void LeftUnit::callbackAttack(Unit* enemy)
{
	enemy->damaged(damage);
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
void LeftUnit::damaged(float d)
{
	hp -= d;

	if (hp <= 0)
	{
		hp = 0;
		isDied = true;

		if (backBuddyUnit != nullptr && backBuddyUnit->isStop)
		{
			backBuddyUnit->buddyUnit = nullptr;
			backBuddyUnit->moveUnit();
		}

		if(!isDieAct)
			this->dieUnit();
	}
}
#pragma endregion

#pragma region schedule function
void LeftUnit::update(float f)
{
	fullHP->setScaleX(static_cast<float>(hp) / static_cast<float>(startHp));

	Rect myRect = getBoundingBox();
	Rect enemyFacRect = Rect(enemyFactoryPos.x + 200, enemyFactoryPos.y, enemyFactory->return_Factory_Sp()->getContentSize().width, enemyFactory->return_Factory_Sp()->getContentSize().height);

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
	//������ �浹���� ���� �� (�켱 ���� = �� > �� ���丮)
	if (!isFighting && myRect.intersectsRect(enemyFacRect))
	{
		//���丮 ����
		log("Attack the enemy factory");
		if (!isAttackFac)
			attackFactory();
	}

	//�Ʊ��� �浹�� ��
	for (Unit* b : unitsL)
	{
		Rect buddyRect = b->getBoundingBox();

		if (myRect.intersectsRect(buddyRect))
		{
			//���� ���� ������ �ִ� ���
			if (myRect.origin.x < buddyRect.origin.x && !isStop)
			{
				isStop = true;
				buddyUnit = b;
				idleUnit();
			}
			//���� ���� ������ �ִ� ���
			if (myRect.origin.x > buddyRect.origin.x)
				backBuddyUnit = b;
		}
		else
		{
			//���� �� �ٽ� �̵�
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