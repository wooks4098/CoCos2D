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
	sprite->initUnit(bubble); //���� �ʱ�ȭ

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
	//���� ������ �ؾ���
	if (bubble.Hp == 0)
		startHp = 100;
	else
		startHp = bubble.Hp;
	hp = startHp;

	if (bubble.MoveSpeed == 0)
		speed = 400;
	else
		speed = bubble.MoveSpeed;

	if (bubble.Damage == 0)
		damage = 10;
	else
		damage = bubble.Damage;

	if (bubble.AttackSpeed == 0)
		attackSpeed = 1;
	else
		attackSpeed = bubble.AttackSpeed;
	
	if (bubble.Defense == 0)
		defense = 5;
	else
		defense = bubble.Defense;
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
	isStop = true;
	isAttackUnit = false;
	isAttackFac = false;

	auto idleAni = Animation::create();
	idleAni->setDelayPerUnit(1);
	idleAni->addSpriteFrameWithFile("Character/C/CMove_0.png");
	auto rep = Repeat::create(Animate::create(idleAni), -1);
	this->runAction(rep);
}

void LeftUnit::moveUnit()
{
	this->stopAllActions();
	isStop = false;
	isAttackUnit = false;
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
	isStop = true;
	isAttackUnit = true;
	isAttackFac = false;

	//Right ���� �ִϸ��̼�
	float aniPerSpeed = (attackSpeed / 6) * 2;
	clampf(aniPerSpeed, 0.1, 0.4);

	auto attackFirstAni = Animation::create();
	attackFirstAni->setDelayPerUnit(aniPerSpeed);
	attackFirstAni->addSpriteFrameWithFile("Character/C/CAttack_0.png");
	attackFirstAni->addSpriteFrameWithFile("Character/C/CAttack_1.png");
	attackFirstAni->addSpriteFrameWithFile("Character/C/CAttack_2.png");
	attackFirstAni->addSpriteFrameWithFile("Character/C/CAttack_3.png");
	auto firstAni = Animate::create(attackFirstAni);

	auto attackSecondAni = Animation::create();
	attackSecondAni->setDelayPerUnit(aniPerSpeed);
	attackSecondAni->addSpriteFrameWithFile("Character/C/CAttack_4.png");
	attackSecondAni->addSpriteFrameWithFile("Character/C/CAttack_5.png");
	auto secondAni = Animate::create(attackSecondAni);

	auto attackFunc = CallFunc::create(CC_CALLBACK_0(LeftUnit::callbackAttack, this, enemy));
	auto sound = CallFunc::create(CC_CALLBACK_0(Unit::sound_attack, this));

	//������ ���� �ִϸ��̼�, ���� �Լ�, ����, ������ �� �� �ִϸ��̼�, ������ ��
	auto seq = Sequence::create(firstAni, attackFunc, sound, secondAni, DelayTime::create(attackSpeed), nullptr);
	auto rep = Repeat::create(seq, -1); //�ִϸ��̼�, ����, ������
	this->runAction(rep);
}

void LeftUnit::attackFactory()
{
	this->stopAllActions();
	isStop = true;
	isAttackUnit = false;
	isAttackFac = true;

	//Right ���� �ִϸ��̼�
	float aniPerSpeed = (attackSpeed / 6) * 2;
	clampf(aniPerSpeed, 0.1, 0.4);

	auto attackFirstAni = Animation::create();
	attackFirstAni->setDelayPerUnit(aniPerSpeed);
	attackFirstAni->addSpriteFrameWithFile("Character/C/CAttack_0.png");
	attackFirstAni->addSpriteFrameWithFile("Character/C/CAttack_1.png");
	attackFirstAni->addSpriteFrameWithFile("Character/C/CAttack_2.png");
	attackFirstAni->addSpriteFrameWithFile("Character/C/CAttack_3.png");
	auto firstAni = Animate::create(attackFirstAni);

	auto attackSecondAni = Animation::create();
	attackSecondAni->setDelayPerUnit(aniPerSpeed);
	attackSecondAni->addSpriteFrameWithFile("Character/C/CAttack_4.png");
	attackSecondAni->addSpriteFrameWithFile("Character/C/CAttack_5.png");
	auto secondAni = Animate::create(attackSecondAni);

	auto attackFunc = CallFunc::create(CC_CALLBACK_0(LeftUnit::callbackAttackFac, this));
	auto sound = CallFunc::create(CC_CALLBACK_0(Unit::sound_attack, this));

	//������ ���� �ִϸ��̼�, ���� �Լ�, ����, ������ �� �� �ִϸ��̼�, ������ ��
	auto seq = Sequence::create(firstAni, attackFunc, sound, secondAni, DelayTime::create(attackSpeed), nullptr);
	auto rep = Repeat::create(seq, -1); //�ִϸ��̼�, ����, ������
	this->runAction(rep);
}

void LeftUnit::dieUnit()
{
	this->stopAllActions();
	isDieAct = true;
	isAttackUnit = false;
	isAttackFac = false;
	isStop = true;

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

	GameManager::GetInstance()->diedUnitL();
	auto remove = CallFunc::create(CC_CALLBACK_0(LeftUnit::removeUnit, this));
	auto removeVec = CallFunc::create(CC_CALLBACK_0(LeftUnit::removeVector, this));
	auto sound = CallFunc::create(CC_CALLBACK_0(Unit::sound_dead, this));
	auto seq = Sequence::create(sound, removeVec, animate, remove, nullptr);
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

		if (!isDieAct)
			this->dieUnit();
	}

	callbackHpBarAni();

	fullHP->setScaleX(static_cast<float>(hp) / static_cast<float>(startHp));
}
#pragma endregion

#pragma region schedule function
void LeftUnit::update(float f)
{
	Rect myRect = getBoundingBox();
	Rect enemyFacRect = Rect(enemyFactoryPos.x - 200, enemyFactoryPos.y, enemyFactoryPos.x, enemyFactory->return_Factory_Sp()->getContentSize().height);

	//���� ���� �տ� �ִ� �����̶��
	if (unitNumber == GameManager::GetInstance()->forwardUnitLeft)
	{
		//������ �浹�� ��
		for (Unit* e : unitsR)
		{
			Rect enemyRect = e->getBoundingBox();

			if (myRect.intersectsRect(enemyRect) && !e->isDied)
			{
				if (!isAttackUnit)
					attackUnit(e);
			}
		}

		//�� ���丮�� �浹�� �� (�켱 ���� = �� > �� ���丮)
		if (!isAttackUnit && myRect.intersectsRect(enemyFacRect))
		{
			//���丮 ����
			if (!isAttackFac)
				attackFactory();
		}

		//�ο�� ���°� �ƴѵ� �����ִٸ� (���� ������ �׾��� ��)
		if (!isAttackUnit && !isAttackFac && isStop)
		{
			isStop = false;
			moveUnit();
		}
	}

	//�� �տ� �Ʊ� ������ �ϳ� �̻� ���� ��
	else
	{
		//�Ʊ��� �浹�� ��
		for (Unit* buddy : unitsL)
		{
			Rect buddyRect = buddy->getBoundingBox();

			if (myRect.intersectsRect(buddyRect))
			{
				//������ �տ� �ִ� ���ְ� �ε����ٸ�
				if (unitNumber > buddy->unitNumber && !isDied)
				{
					isStop = true;
					buddyUnit = buddy;
					idleUnit();
				}
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
			}
		}

	}
}
#pragma endregion