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

	sprite->sound_create();

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
		speed = bubble.MoveSpeed;

	if (bubble.Damage == 0)
		damage = 20;
	else
		damage = bubble.Damage;
}
#pragma endregion

#pragma region remove
//�����ϴ� �Լ�
void LeftUnit::removeVector()
{
	if (unitsL.contains(this))
		unitsL.eraseObject(this);
}

void LeftUnit::removeUnit()
{
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

	auto seq = Sequence::create(Animate::create(attackAni), CallFunc::create(CC_CALLBACK_0(LeftUnit::callbackAttack, this, enemy)), CallFunc::create(CC_CALLBACK_0(Unit::sound_attack, this)), DelayTime::create(1.5f), nullptr); //�ִϸ��̼�+����, ������ ����������
	auto rep = Repeat::create(seq, -1); //�ִϸ��̼�, ����, ������
	this->runAction(rep);
}

void LeftUnit::attackFactory()
{
	this->stopAllActions();
	isAttackFac = true;
	isFighting = false;

	//Right ���� �ִϸ��̼�
	auto attackAni = Animation::create();
	attackAni->setDelayPerUnit(0.3f);
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_0.png");
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_1.png");
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_2.png");
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_3.png");
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_4.png");
	attackAni->addSpriteFrameWithFile("Character/C/CAttack_5.png");

	auto seq = Sequence::create(Animate::create(attackAni), CallFunc::create(CC_CALLBACK_0(LeftUnit::callbackAttackFac, this)), CallFunc::create(CC_CALLBACK_0(Unit::sound_attackFac, this)), DelayTime::create(1.5f), nullptr); //�ִϸ��̼�+����, ������ ����������
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
	auto removeVec = CallFunc::create(CC_CALLBACK_0(LeftUnit::removeVector, this));
	auto seq = Sequence::create(CallFunc::create(CC_CALLBACK_0(Unit::sound_dead, this)), removeVec, animate, remove, nullptr);
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

		if (!isDieAct)
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

	//������ �浹�� ��
	for (Unit* e : unitsR)
	{
		Rect enemyRect = e->getBoundingBox();

		if (myRect.intersectsRect(enemyRect) && !e->isDied)
		{
			if (!isFighting)
				attackUnit(e);
		}
	}

	//�� ���丮�� �浹�� �� (�켱 ���� = �� > �� ���丮)
	if (!isFighting && myRect.intersectsRect(enemyFacRect))
	{
		//���丮 ����
		if (!isAttackFac)
			attackFactory();
	}

	//�Ʊ��� �浹�� ��
	for (Unit* buddy : unitsL)
	{
		Rect buddyRect = buddy->getBoundingBox();

		if (myRect.intersectsRect(buddyRect) && !buddy->isDied)
		{
			//������ ���� ������ ����� ���丮�� �� ����� ��
			if (myRect.origin.x < buddyRect.origin.x && isStop == false)
			{
				isStop = true;
				buddyUnit = buddy;
				idleUnit();
			}

			//�տ� �浹�� �Ʊ� ����
			if (myRect.origin.x > buddyRect.origin.x)
				backBuddyUnit = buddy;
		}
		else
		{
			//���� �� �ٽ� �̵�
			if (buddy == buddyUnit)
			{
				isStop = false;
				buddyUnit = nullptr;
				moveUnit();
			}
			
			//�տ� �浹�� �Ʊ� ������ �׾��� ��
			if (buddy == backBuddyUnit)
			{
				backBuddyUnit = nullptr;
			}
		}
	}
}
#pragma endregion