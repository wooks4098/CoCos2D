#include "Factory.h"

Factory::Factory()
{
	winSize = Director::getInstance()->getWinSize(); //ȭ���� ������ ���ϱ�
	MaxHp = 100;
	CurHp = MaxHp;
}
void Factory::Create(int factoryNumber)
{
	if (factoryNumber == FACTORY_RIGHT)
		isRight = true;
	Create_HpBar();
	Create_HpDownMenu();
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


void Factory::HpDown(Ref* Sender)
{
	if (CurHp <= 0)
		return;
	CurHp -= 10;
	//Hp_Bar->setPosition(Vec2(winSize.width + (560 / MaxHp * (MaxHp - CurHp)), winSize.height));
	if(CurHp <= 0)
		Hp_Bar->setScaleX(0);
	else
		Hp_Bar->setScaleX((float)CurHp/(float)MaxHp);
}


void CreatUnit()
{

}