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

	sprite->sound_create();

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
	if (bubble.Hp == 0)
		startHp = 80;
	else
		startHp = 80 + bubble.Hp;
	hp = startHp;

	if (bubble.MoveSpeed == 0)
		speed = 200;
	else
		speed = 200 + bubble.MoveSpeed;

	if (bubble.Damage == 0)
		damage = 10;
	else
		damage = 10 + bubble.Damage;

	if (bubble.AttackSpeed == 0)
		attackSpeed = 0.5;
	else
		attackSpeed = 0.5 * (bubble.AttackSpeed);

	if (bubble.Defense == 0)
		defense = 5;
	else
		defense = 5 + bubble.Defense;
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
	isStop = true;
	isAttackUnit = false;
	isAttackFac = false;

	auto idleAni = Animation::create();
	idleAni->setDelayPerUnit(1);
	idleAni->addSpriteFrameWithFile("Character/A/AMove_0.png");
	auto rep = Repeat::create(Animate::create(idleAni), -1);
	this->runAction(rep);
}

void RightUnit::moveUnit()
{
	this->stopAllActions();
	isStop = false;
	isAttackUnit = false;
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
	isStop = true;
	isAttackUnit = true;
	isAttackFac = false;

	//Left공격 애니메이션
	float aniPerSpeed = (attackSpeed / 6) * 2;
	clampf(aniPerSpeed, 0.1, 0.4);
	
	auto attackFirstAni = Animation::create();
	attackFirstAni->setDelayPerUnit(aniPerSpeed);
	attackFirstAni->addSpriteFrameWithFile("Character/A/AAttack_0.png");
	attackFirstAni->addSpriteFrameWithFile("Character/A/AAttack_1.png");
	attackFirstAni->addSpriteFrameWithFile("Character/A/AAttack_2.png");
	attackFirstAni->addSpriteFrameWithFile("Character/A/AAttack_3.png");
	auto firstAni = Animate::create(attackFirstAni);

	auto attackSecondAni = Animation::create();
	attackSecondAni->setDelayPerUnit(aniPerSpeed);
	attackSecondAni->addSpriteFrameWithFile("Character/A/AAttack_4.png");
	attackSecondAni->addSpriteFrameWithFile("Character/A/AAttack_5.png");
	auto secondAni = Animate::create(attackSecondAni);

	auto attackFunc = CallFunc::create(CC_CALLBACK_0(RightUnit::callbackAttack, this, enemy));
	auto sound = CallFunc::create(CC_CALLBACK_0(Unit::sound_attack, this));

	//검으로 베는 애니메이션, 공격 함수, 사운드, 검으로 벤 후 애니메이션, 딜레이 순
	auto seq = Sequence::create(firstAni, attackFunc, sound, secondAni, DelayTime::create(attackSpeed), nullptr);
	auto rep = Repeat::create(seq, -1); //애니메이션, 공격, 딜레이
	this->runAction(rep);
}

void RightUnit::attackFactory()
{
	this->stopAllActions();
	isStop = true;
	isAttackUnit = false;
	isAttackFac = true;

	//Left공격 애니메이션
	float aniPerSpeed = (attackSpeed / 6) * 2;
	clampf(aniPerSpeed, 0.2, 0.4);

	auto attackFirstAni = Animation::create();
	attackFirstAni->setDelayPerUnit(aniPerSpeed);
	attackFirstAni->addSpriteFrameWithFile("Character/A/AAttack_0.png");
	attackFirstAni->addSpriteFrameWithFile("Character/A/AAttack_1.png");
	attackFirstAni->addSpriteFrameWithFile("Character/A/AAttack_2.png");
	attackFirstAni->addSpriteFrameWithFile("Character/A/AAttack_3.png");
	auto firstAni = Animate::create(attackFirstAni);

	auto attackSecondAni = Animation::create();
	attackSecondAni->setDelayPerUnit(aniPerSpeed);
	attackSecondAni->addSpriteFrameWithFile("Character/A/AAttack_4.png");
	attackSecondAni->addSpriteFrameWithFile("Character/A/AAttack_5.png");
	auto secondAni = Animate::create(attackSecondAni);

	auto attackFunc = CallFunc::create(CC_CALLBACK_0(RightUnit::callbackAttackFac, this));
	auto sound = CallFunc::create(CC_CALLBACK_0(Unit::sound_attack, this));

	//검으로 베는 애니메이션, 공격 함수, 사운드, 검으로 벤 후 애니메이션, 딜레이 순
	auto seq = Sequence::create(firstAni, attackFunc, sound, secondAni, DelayTime::create(attackSpeed), nullptr);
	auto rep = Repeat::create(seq, -1); //애니메이션, 공격, 딜레이
	this->runAction(rep);
}

void RightUnit::dieUnit()
{
	this->stopAllActions();
	isDieAct = true;
	isAttackUnit = false;
	isAttackFac = false;
	isStop = true;

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
	
	GameManager::GetInstance()->diedUnitR();
	auto remove = CallFunc::create(CC_CALLBACK_0(RightUnit::removeUnit, this));
	auto removeVec = CallFunc::create(CC_CALLBACK_0(RightUnit::removeVector, this));
	auto sound = CallFunc::create(CC_CALLBACK_0(Unit::sound_dead, this));
	auto seq = Sequence::create(sound, removeVec, animate, remove, nullptr);
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

		if (!isDieAct)
			this->dieUnit();
	}
	
	callbackHpBarAni();

	fullHP->setScaleX(static_cast<float>(hp) / static_cast<float>(startHp));
}
#pragma endregion

#pragma region schedule function
void RightUnit::update(float f)
{
	Rect myRect = getBoundingBox();
	Rect enemyFacRect = Rect(enemyFactoryPos.x, enemyFactoryPos.y, 200, enemyFactory->return_Factory_Sp()->getContentSize().height);

	//내가 제일 앞에 있는 유닛이라면
	if (unitNumber == GameManager::GetInstance()->forwardUnitRight)
	{
		//적군과 충돌할 때
		for (Unit* e : unitsL)
		{
			Rect enemyRect = e->getBoundingBox();

			if (myRect.intersectsRect(enemyRect) && !e->isDied)
			{
				if (!isAttackUnit)
					attackUnit(e);
			}
		}

		//적 팩토리와 충돌할 때 (우선 순위 = 적 > 적 팩토리)
		if (!isAttackUnit && myRect.intersectsRect(enemyFacRect))
		{
			//팩토리 공격
			if (!isAttackFac)
				attackFactory();
		}
		
		//싸우는 상태가 아닌데 멈춰있다면 (앞의 유닛이 죽었을 때)
		if (!isAttackUnit && !isAttackFac && isStop)
		{
			isStop = false;
			moveUnit();
		}
	}

	//내 앞에 아군 유닛이 하나 이상 있을 때
	else
	{
		//아군과 충돌할 때
		for (Unit* buddy : unitsR)
		{
			Rect buddyRect = buddy->getBoundingBox();

			if (myRect.intersectsRect(buddyRect))
			{
				//나보다 앞에 있는 유닛과 부딪혔다면
				if (unitNumber > buddy->unitNumber && !isDied)
				{
					isStop = true;
					buddyUnit = buddy;
					idleUnit();
				}
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
		}

	}
}
#pragma endregion