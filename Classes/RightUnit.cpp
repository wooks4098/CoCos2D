#include "RightUnit.h"

extern Vector<Unit*> unitsL;
extern Vector<Unit*> unitsR;

#pragma region create
Unit* RightUnit::createUnit(Factory* myFac, Factory* enemyFac)
{
	//���������� Unit�� �������� ���� ��� ���α׷��� ���� �ʵ��� ����ó��
	Unit* sprite = new (std::nothrow)RightUnit();

	const char* fileName;

	fileName = "Character/A/AMove_0.png";

	sprite->myFactory = myFac;
	sprite->enemyFactory = enemyFac;

	sprite->initData();
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
void RightUnit::initUnit()
{
	maxHp = 20;
	hp = maxHp;
	speed = 200;
	power = 2;

	fullHP->setScaleX(1); //���� ��...
}
#pragma endregion

#pragma region remove
//�����ϴ� �Լ�
void RightUnit::removeUnit()
{
	if (unitsR.contains(this))
		unitsR.eraseObject(this);
	auto removeSelf = RemoveSelf::create(true);
	this->runAction(removeSelf);
}
#pragma endregion

#pragma region action & animation
void RightUnit::idleUnit()
{
	this->stopAllActions();
	isFighting = false;
	isAttackFac = false;

	auto idleAni = Animation::create();
	idleAni->setDelayPerUnit(0.3f);
	idleAni->addSpriteFrameWithFile("Character/A/AMove_0.png");
	auto rep = Repeat::create(Animate::create(idleAni), -1);
	this->runAction(rep);
}

void RightUnit::moveUnit()
{
	this->stopAllActions();
	isFighting = false;
	isAttackFac = false;

	float distance = fabs(enemyFactory->return_Factory_Sp()->getPosition().x - getPosition().x);
	auto move = MoveTo::create(distance / speed, enemyFactory->return_Factory_Sp()->getPosition());

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

void RightUnit::attackUnit(Unit* enemy)
{
	this->stopAllActions();
	this->isFighting = true;
	isAttackFac = false;

	//Left���� �ִϸ��̼�
	auto attackAni = Animation::create();
	attackAni->setDelayPerUnit(0.3f);
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_0.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_1.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_2.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_3.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_4.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_5.png");
	
	auto seq = Sequence::create(Animate::create(attackAni), CallFunc::create(CC_CALLBACK_0(RightUnit::callbackAttack, this, enemy)), DelayTime::create(1.5f), nullptr); //�ִϸ��̼�+����, ������ ����������
	auto rep = Repeat::create(seq, -1); //�ִϸ��̼�, ����, ������
	this->runAction(rep);
}

void RightUnit::attackFactory()
{
	this->stopAllActions();
	isAttackFac = true;

	//Left���� �ִϸ��̼�
	auto attackAni = Animation::create();
	attackAni->setDelayPerUnit(0.3f);
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_0.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_1.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_2.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_3.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_4.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_5.png");

	auto seq = Sequence::create(Animate::create(attackAni), CallFunc::create(CC_CALLBACK_0(RightUnit::callbackAttackFac, this)), DelayTime::create(1.5f), nullptr); //�ִϸ��̼�+����, ������ ����������
	auto rep = Repeat::create(seq, -1); //�ִϸ��̼�, ����, ������
	this->runAction(rep);
}

void RightUnit::dieUnit()
{
	this->stopAllActions();
	isDieAct = true;

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

	auto remove = CallFunc::create(CC_CALLBACK_0(RightUnit::removeUnit, this));
	auto seq = Sequence::create(animate, remove, nullptr);
	this->runAction(seq);

	auto fadeout = Spawn::create(DelayTime::create(2.4f), FadeOut::create(1.2f), nullptr);
	emptyHP->runAction(fadeout);
}
#pragma endregion

#pragma region callback function
void RightUnit::callbackAttack(Unit* enemy)
{
	enemy->damaged(power);
	if (enemy->isDied)
	{
		moveUnit();
	}
}

void RightUnit::callbackAttackFac()
{
	enemyFactory->Factory_Hp_Down();
}

//���� �޴� �Լ�
void RightUnit::damaged(float damage)
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
#pragma endregion

#pragma region schedule function
void RightUnit::update(float f)
{
	fullHP->setScaleX(static_cast<float>(hp) / static_cast<float>(maxHp));

	Rect myRect = getBoundingBox();
	Rect enemyFacRect = enemyFactory->return_Factory_Sp()->getBoundingBox();

	//������ �浹�� ��
	for (Unit* e : unitsL)
	{
		Rect enemyRect = e->getBoundingBox();

		//�� ������ �浹���� ��
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
	for (Unit* b : unitsR)
	{
		Rect buddyRect = b->getBoundingBox();

		if (myRect.intersectsRect(buddyRect))
		{
			//���ֺ��� �浹�� �Ʊ� ������ �� ����� ���丮�� ����� ��
			if (buddyRect.origin.x < myRect.origin.x && isStop == false)
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