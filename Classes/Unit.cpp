#include "Unit.h"

#pragma region init
void Unit::initData()
{
	myFactoryPos = Vec2(myFactory->return_Factory_Sp()->getPosition().x, myFactory->return_Factory_Sp()->getPosition().y - 60);
	enemyFactoryPos = Vec2(enemyFactory->return_Factory_Sp()->getPosition().x, enemyFactory->return_Factory_Sp()->getPosition().y - 60);

	this->setPosition(this->myFactoryPos);
}
#pragma endregion

#pragma region sound
void Unit::sound_create()
{
	SoundManager::GetInstance()->Play(Unit_Create);
}

void Unit::sound_attack()
{
	int randSound = rand() % 3;
		switch (randSound)
		{
			case 0:
			{
				SoundManager::GetInstance()->Play(Unit_Attack_0);
				break;
			}
			case 1:
			{
				SoundManager::GetInstance()->Play(Unit_Attack_1);
				break;
			}
			case 2:
			{
				SoundManager::GetInstance()->Play(Unit_Attack_2);
				break;
			}
		}
}

void Unit::sound_attackFac()
{
	SoundManager::GetInstance()->Play(Factory_Damage);
}

void Unit::sound_upgrade()
{
	SoundManager::GetInstance()->Play(Unit_Upgrade);
}

void Unit::sound_dead()
{
	int randSound = rand() % 3;
	switch (randSound)
	{
		case 0:
		{
			SoundManager::GetInstance()->Play(Unit_Dead_0);
			break;
		}
		case 1:
		{
			SoundManager::GetInstance()->Play(Unit_Dead_1);
			break;
		}
		case 2:
		{
			SoundManager::GetInstance()->Play(Unit_Dead_2);
			break;
		}
	}
}
#pragma endregion

#pragma region HpBar
void Unit::createHpBar()
{
	//hp¹Ù
	emptyHP = Sprite::create("Character/emptyHP.png");
	fullHP = Sprite::create("Character/fullHP.png");

	emptyHP->setPosition(Vec2(getBoundingBox().size.width / 2 - emptyHP->getBoundingBox().size.width / 2, getBoundingBox().size.height));
	fullHP->setPosition(Vec2(getBoundingBox().size.width / 2 - fullHP->getBoundingBox().size.width / 2, getBoundingBox().size.height));

	emptyHP->setAnchorPoint(Vec2(0, 0));
	fullHP->setAnchorPoint(Vec2(0, 0));

	this->addChild(emptyHP, 4);
	this->addChild(fullHP, 5);

	auto fadeTo = FadeTo::create(0, 0);
	auto fadeIn = FadeIn::create(1.5f);
	auto seq = Sequence::create(fadeTo, fadeIn, nullptr);

	emptyHP->runAction(seq);
	fullHP->runAction(seq);
}

void Unit::callbackHpBarAni()
{
	auto first = ScaleTo::create(0.05, (static_cast<float>(hp) / static_cast<float>(startHp)) * 1.1f , 1);
	auto second = ScaleTo::create(0.05, (static_cast<float>(hp) / static_cast<float>(startHp)) * 0.9f, 1);
	auto third = ScaleTo::create(0.05, static_cast<float>(hp) / static_cast<float>(startHp) , 1);

	auto seq = Sequence::create(first, second, third, nullptr);
	fullHP->runAction(seq);
}
#pragma endregion

void Unit::died()
{
	this->dieUnit();
}