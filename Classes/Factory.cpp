#include "Factory.h"

Factory::Factory()
{
	winSize = Director::getInstance()->getWinSize(); //화면의 사이즈 구하기
	MaxHp = 100;
	CurHp = MaxHp;
}

void Factory::Create_HpBar()
{
	Hp_Bar_Back = Sprite::create("Wook_Test/Test_Hp_Back.png");
	Hp_Bar_Back->setAnchorPoint(Vec2(1, 1));
	Hp_Bar_Back->setPosition(winSize.width, winSize.height);

	Hp_Bar = Sprite::create("Wook_Test/Test_Hp.png");
	Hp_Bar->setAnchorPoint(Vec2(1, 1));
	Hp_Bar->setPosition(winSize.width, winSize.height);
	
}

void Factory::Create_HpDownMenu()
{
	auto Test_Hpdown_btn = MenuItemImage::create("Wook_Test/Test_Hpdown_1.png", "Wook_Test/Test_Hpdown_2.png", CC_CALLBACK_1(Factory::HpDown, this));
	Test_Hpdown_btn->setPosition(winSize.width / 3, winSize.height / 2);

	menu = Menu::create(Test_Hpdown_btn, nullptr);
	menu->setPosition(Vec2::ZERO);
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