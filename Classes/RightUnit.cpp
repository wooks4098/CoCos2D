#include "RightUnit.h"

extern Vector<Unit*> unitsL;
extern Vector<Unit*> unitsR;

Unit* RightUnit::createUnitR(Factory* myFac, Factory* enemyFac)
{
	//정상적으로 Unit이 생성되지 않은 경우 프로그램이 죽지 않도록 예외처리
	Unit* sprite = new (std::nothrow)RightUnit();

	const char* fileName;

	fileName = "Character/A/AMove_0.png";



	sprite->myFactory = myFac;
	sprite->enemyFactory = enemyFac;

	sprite->initUnit(); //유닛 초기화

	sprite->scheduleUpdate();

	if (sprite && sprite->initWithFile(fileName))
	{
		sprite->autorelease(); //스프라이트 사용이 끝날 때 자동으로 메모리에서 제거될 수 있도록
		return sprite;
	}

	CC_SAFE_DELETE(sprite); //사용이 끝난 스프라이트 제거
	return nullptr;
}

void RightUnit::idleUnit()
{
	this->stopAllActions();

	auto idleAni = Animation::create();
	idleAni->setDelayPerUnit(0.3f);
	idleAni->addSpriteFrameWithFile("Character/A/AMove_0.png");
	auto rep = Repeat::create(Animate::create(idleAni), -1);
	this->runAction(rep);
}
void RightUnit::moveUnit()
{
	this->stopAllActions();

	float distance = fabs(enemyFactory->return_Factory_Sp()->getPosition().x - getPosition().x);
	auto move = MoveTo::create(distance / speed, enemyFactory->return_Factory_Sp()->getPosition());

	//Left 이동 애니메이션
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

	//Left공격 애니메이션
	auto attackAni = Animation::create();
	attackAni->setDelayPerUnit(0.3f);
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_0.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_1.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_2.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_3.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_4.png");
	attackAni->addSpriteFrameWithFile("Character/A/AAttack_5.png");
	auto spawn = Spawn::create(Animate::create(attackAni), CallFunc::create(CC_CALLBACK_0(RightUnit::callbackAttack, this, enemy)), nullptr); //애니메이션, 공격 동시에
	auto seq = Sequence::create(spawn, DelayTime::create(1.5f), nullptr); //애니메이션+공격, 딜레이 순차적으로
	auto rep = Repeat::create(seq, -1); //애니메이션, 공격, 딜레이
	this->runAction(rep);
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
void RightUnit::initUnit()
{

	this->setPosition(this->myFactory->return_Factory_Sp()->getPosition());

	//hp바
	emptyHP = Sprite::create("Character/emptyHP.png");
	fullHP = Sprite::create("Character/fullHP.png");

	emptyHP->setPosition(Vec2(0,  300));
	fullHP->setPosition(Vec2(0,  300));

	emptyHP->setAnchorPoint(Vec2(0, 0));
	fullHP->setAnchorPoint(Vec2(0, 0));

	this->addChild(emptyHP, 3);
	this->addChild(fullHP, 4);


	maxHp = 20;
	hp = maxHp;
	speed = 200;
	power = 2;
	log("Right HP : %d", hp);
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
void RightUnit::update(float f)
{
	fullHP->setScaleX(hp / maxHp);

	Rect myRect = getBoundingBox();

	//적군과 충돌할 때
	for (Unit* e : unitsL)
	{
		Rect enemyRect = e->getBoundingBox();

		//두 유닛이 충돌했을 때
		if (myRect.intersectsRect(enemyRect))
		{
			if (!isFighting && !e->isDied)
				attackUnit(e);
		}
	}

	//아군과 충돌할 때
	for (Unit* b : unitsR)
	{
		Rect buddyRect = b->getBoundingBox();

		if (myRect.intersectsRect(buddyRect))
		{
			//유닛보다 충돌한 아군 유닛이 더 상대편 팩토리와 가까울 때
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
