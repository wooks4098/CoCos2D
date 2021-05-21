#include "Factory.h"

Factory::Factory()
{
	winSize = Director::getInstance()->getWinSize(); //ȭ���� ������ ���ϱ�
	CreatUnit_timeCheck = 30;	
	CreatUnit_time = 0;		
	MaxHp = 100;
	CurHp = MaxHp;
}





#pragma region ����
void Factory::Create(int factoryNumber)
{
	if (factoryNumber == FACTORY_RIGHT)
		isRight = true;
	//��������Ʈ ����
	Create_HpBar();
	Create_HpDownMenu();
	Create_Factory_Sp();

}
void Factory::Create_Factory_Sp()
{
	if (isRight)
	{//���� ��ġ: ������
		Factory_sp = Sprite::create("Wook_Test/Test_Factory.png");
		Factory_sp->setAnchorPoint(Vec2(1, 0.5));
		Factory_sp->setPosition(winSize.width, winSize.height / 2);
	}
	else
	{//���� ��ġ ����
		Factory_sp = Sprite::create("Wook_Test/Test_Factory.png");
		Factory_sp->setAnchorPoint(Vec2(0, 0.5));
		Factory_sp->setPosition(0, winSize.height / 2);
	}
}

void Factory::Create_HpBar()
{
	if (isRight)
	{//���� ��ġ: ������
		Hp_Bar_Back = Sprite::create("Wook_Test/Test_Hp_Back.png");
		Hp_Bar_Back->setAnchorPoint(Vec2(1, 1));
		Hp_Bar_Back->setPosition(winSize.width, winSize.height);

		Hp_Bar = Sprite::create("Wook_Test/Test_Hp.png");
		Hp_Bar->setAnchorPoint(Vec2(1, 1));
		Hp_Bar->setPosition(winSize.width, winSize.height);


	}
	else
	{//���� ��ġ ����
		Hp_Bar_Back = Sprite::create("Wook_Test/Test_Hp_Back.png");
		Hp_Bar_Back->setAnchorPoint(Vec2(0, 1));
		Hp_Bar_Back->setPosition(0, winSize.height);

		Hp_Bar = Sprite::create("Wook_Test/Test_Hp.png");
		Hp_Bar->setAnchorPoint(Vec2(0, 1));
		Hp_Bar->setPosition(0, winSize.height);
	}


}

void Factory::Create_HpDownMenu()
{
	if (isRight)
	{
		auto Test_Hpdown_btn = MenuItemImage::create("Wook_Test/Test_Hpdown_1.png", "Wook_Test/Test_Hpdown_2.png", CC_CALLBACK_1(Factory::HpDown, this));

		Test_Hpdown_btn->setPosition(winSize.width, winSize.height / 2);
		Test_Hpdown_btn->setAnchorPoint(Vec2(1, 1));
		menu = Menu::create(Test_Hpdown_btn, nullptr);

		menu->setPosition(Vec2::ZERO);
	}
	else
	{
		auto Test_Hpdown_btn = MenuItemImage::create("Wook_Test/Test_Hpdown_1.png", "Wook_Test/Test_Hpdown_2.png", CC_CALLBACK_1(Factory::HpDown, this));

		Test_Hpdown_btn->setPosition(0, winSize.height / 2);
		Test_Hpdown_btn->setAnchorPoint(Vec2(0, 1));
		menu = Menu::create(Test_Hpdown_btn, nullptr);

		menu->setPosition(Vec2::ZERO);
	}

}


#pragma endregion

#pragma region ���丮 ����
void Factory::Factory_Damage_Action()
{
	auto First = Spawn::create(ScaleBy::create(0.08, 1.1), nullptr);
	auto Second = Spawn::create(ScaleBy::create(0.08, 0.9), nullptr);
	auto Third = Spawn::create(ScaleBy::create(0.08, 1), nullptr);
	auto Action = Sequence::create(First, Second, Third, nullptr);
	Factory_sp->runAction(Action);
}

void Factory::Factory_Hit_Check(Sprite* _unit)
{
	if (Factory_sp->getBoundingBox().intersectsRect(_unit->getBoundingBox()))
	{//���ְ� �浹
		Factory_Hp_Down();
	}
}

void Factory::Factory_Hp_Down()
{
	if (CurHp <= 0)
		return;
	Factory_Damage_Action();
	CurHp -= 10;
	if (CurHp <= 0)
		Hp_Bar->setScaleX(0);
	else
		Hp_Bar->setScaleX((float)CurHp / (float)MaxHp);
}
#pragma endregion

#pragma region ���ְ���
void Factory::Change_CreatUnit_Time(float time)
{
	CreatUnit_time = time * 10;
	CreatUnit_timeCheck = 0;
}

void Factory::CreatUnit()
{
	CreatUnit_time += 0.1f;
	if (CreatUnit_time >= CreatUnit_timeCheck)
	{
		//���� ���� �Լ� ���
		CreatUnit_time = 0;
	}

}

#pragma endregion

#pragma region �޴� �ݹ�

void Factory::HpDown(Ref* Sender)
{
	if (CurHp <= 0)
		return;
	Factory_Damage_Action();
	CurHp -= 10;
	//Hp_Bar->setPosition(Vec2(winSize.width + (560 / MaxHp * (MaxHp - CurHp)), winSize.height));
	if (CurHp <= 0)
		Hp_Bar->setScaleX(0);
	else
		Hp_Bar->setScaleX((float)CurHp / (float)MaxHp);
}
#pragma endregion

