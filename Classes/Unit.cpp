#include "Unit.h"

//초기화
void Unit::initData()
{
	myFactoryPos = Vec2(myFactory->return_Factory_Sp()->getPosition().x, myFactory->return_Factory_Sp()->getPosition().y - 50);
	enemyFactoryPos = Vec2(enemyFactory->return_Factory_Sp()->getPosition().x, enemyFactory->return_Factory_Sp()->getPosition().y - 50);

	this->setPosition(this->myFactoryPos);

	//hp바
	emptyHP = Sprite::create("Character/emptyHP.png");
	fullHP = Sprite::create("Character/fullHP.png");

	emptyHP->setPosition(Vec2(0, 300));
	fullHP->setPosition(Vec2(0, 300));

	emptyHP->setAnchorPoint(Vec2(0, 0));
	fullHP->setAnchorPoint(Vec2(0, 0));
	
	this->addChild(emptyHP, 4);
	this->addChild(fullHP, 5);
}

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
