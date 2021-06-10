#include "RightUnit.h"

extern Vector<Unit*> unitsL;
extern Vector<Unit*> unitsR;

#pragma region create
Unit* RightUnit::createUnit(Factory* myFac, Factory* enemyFac, BUBBLE bubble)
{
	//정상적으로 Unit이 생성되지 않은 경우 프로그램이 죽지 않도록 예외처리
	Unit* sprite = new (std::nothrow)RightUnit();

	const char* fileName;

	fileName = "Character/A/AMove_0.png";

	sprite->myFactory = myFac;
	sprite->enemyFactory = enemyFac;

	sprite->initData();
	sprite->initUnit(bubble); //유닛 초기화

	sprite->scheduleUpdate();

	if (sprite && sprite->initWithFile(fileName))
	{
		sprite->autorelease(); //스프라이트 사용이 끝날 때 자동으로 메모리에서 제거될 수 있도록
		return sprite;
	}

	CC_SAFE_DELETE(sprite); //사용이 끝난 스프라이트 제거
	return nullptr;
}
#pragma endregion

#pragma region init
void RightUnit::initUnit(BUBBLE bubble)
{
	//수정해야함
	if(bubble.Hp == 0)
		startHp = 40;
	else
		startHp = bubble.Hp;
	hp = startHp;

	if (bubble.MoveSpeed == 0)
		speed = 300;
	else
		speed = bubble.MoveSpeed;

	if (bubble.Damage == 0)
		damage = 10;
	else
		damage = bubble.Damage;
}
#pragma endregion

#pragma region remove
//제거하는 함수
void RightUnit::removeVector()
{
	if (unitsL.contains(this))
		unitsL.eraseObject(this);
}

void RightUnit::removeUnit()
{
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

	float distance = fabs(myFactoryPos.x - enemyFactoryPos.x);
	auto move = MoveTo::create(distance / speed, enemyFactoryPos);

	//Right 이동 애니메이션
	auto moveAni = Animation::create();
	moveAni->setDelayPerUnit(0.1f);
	moveAni->addSpriteFrameWithFile("Character/A/AMove_0.png");
	moveAni->addSpriteFrameWithFile("Character/A/AMove_1.png");
	moveAni->addSpriteFrameWithFile("Character/A/AMove_2.png");
	moveAni->addSpriteFrameWithFile("Character/A/AMove_3.png");
	moveAni->addSpriteFrameWithFile("Character/A/AMove_4.png");
	moveAni->addSpriteFrameWithFile("Character/A/AMove_5.png");
	auto animate = Animate::create(moveAni);
	auto rep = Repeat::create(animate, -1);

	this->runAction(move);
	this->runAction(rep);
}

void RightUnit::attackUnit(Unit* enemy)
{
	this->stopAllActions();
	this->isFighting = true;
	isAttackFac = false;

	//Left공격 애니메이션
	auto attackAni = Animation::create();
	attackAni->setDelayPerUnit(0.3f);
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_0.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_1.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_2.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_3.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_4.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_5.png");
	
	auto seq = Sequence::create(Animate::create(attackAni), CallFunc::create(CC_CALLBACK_0(RightUnit::callbackAttack, this, enemy)), DelayTime::create(1.5f), nullptr); //애니메이션+공격, 딜레이 순차적으로
	auto rep = Repeat::create(seq, -1); //애니메이션, 공격, 딜레이
	this->runAction(rep);
}

void RightUnit::attackFactory()
{
	this->stopAllActions();
	isAttackFac = true;
	isFighting = false;

	//Left공격 애니메이션
	auto attackAni = Animation::create();
	attackAni->setDelayPerUnit(0.3f);
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_0.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_1.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_2.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_3.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_4.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_5.png");

	auto seq = Sequence::create(Animate::create(attackAni), CallFunc::create(CC_CALLBACK_0(RightUnit::callbackAttackFac, this)), DelayTime::create(1.5f), nullptr); //애니메이션+공격, 딜레이 순차적으로
	auto rep = Repeat::create(seq, -1); //애니메이션, 공격, 딜레이
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
	auto removeVec = CallFunc::create(CC_CALLBACK_0(RightUnit::removeVector, this));
	auto seq = Sequence::create(removeVec, animate, remove, nullptr);
	this->runAction(seq);

	auto fadeout = Spawn::create(DelayTime::create(2.4f), FadeOut::create(1.2f), nullptr);
	emptyHP->runAction(fadeout);
}
#pragma endregion

#pragma region callback function
void RightUnit::callbackAttack(Unit* enemy)
{
	enemy->damaged(damage);
	if (enemy->isDied)
	{
		moveUnit();
	}
}

void RightUnit::callbackAttackFac()
{
	enemyFactory->Factory_Hp_Down();
}

//공격 받는 함수
void RightUnit::damaged(float d)
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
void RightUnit::update(float f)
{
	fullHP->setScaleX(static_cast<float>(hp) / static_cast<float>(startHp));

	Rect myRect = getBoundingBox();
	Rect enemyFacRect = Rect(enemyFactoryPos.x + 200, enemyFactoryPos.y, enemyFactory->return_Factory_Sp()->getContentSize().width, enemyFactory->return_Factory_Sp()->getContentSize().height);

	//적군과 충돌할 때
	for (Unit* e : unitsL)
	{
		Rect enemyRect = e->getBoundingBox();

		if (myRect.intersectsRect(enemyRect) && !e->isDied)
		{
			if (!isFighting)
				attackUnit(e);
		}
	}

	//적 팩토리와 충돌할 때 (우선 순위 = 적 > 적 팩토리)
	if (!isFighting && myRect.intersectsRect(enemyFacRect))
	{
		//팩토리 공격
		if (!isAttackFac)
			attackFactory();
	}

	//아군과 충돌할 때
	for (Unit* buddy : unitsR)
	{
		Rect buddyRect = buddy->getBoundingBox();
		
		if (myRect.intersectsRect(buddyRect) && !buddy->isDied)
		{
			//나보다 버디 유닛이 상대편 팩토리와 더 가까울 때
			if (buddyRect.origin.x < myRect.origin.x && isStop == false)
			{
				isStop = true;
				buddyUnit = buddy;
				idleUnit();
			}

			//앞에 충돌한 아군 유닛
			if (myRect.origin.x > buddyRect.origin.x)
				backBuddyUnit = buddy;
		}
		else
		{
			//전투 후 다시 이동
			if (buddy == buddyUnit)
			{
				isStop = false;
				buddyUnit = nullptr;
				moveUnit();
			}
		}

		//앞에 충돌한 아군 유닛이 죽었을 때
		if (buddy == backBuddyUnit)
		{
			backBuddyUnit = nullptr;
		}
	}
}
#pragma endregion