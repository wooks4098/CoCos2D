#include "Factory.h"

Factory::Factory()
{
	winSize = Director::getInstance()->getWinSize(); //화면의 사이즈 구하기
	CreatUnit_timeCheck = 30;	
	CreatUnit_time = 0;		
	MaxHp = 100;
	CurHp = MaxHp;

	Circle_bubble.key = None_Circle;
	Rhombus_bubble.key = None_Rhombus;
}

#pragma region 생성
void Factory::Create(int factoryNumber)
{
	if (factoryNumber == FACTORY_RIGHT)
		isRight = true;
	else
		isRight = false;
	//스프라이트 생성
	Create_HpBar();
	Create_HpDownMenu();
	Create_Factory_Sp();
	Create_Bubble();

}
void Factory::Create_Factory_Sp()
{
	if (isRight)
	{//공장 위치: 오른쪽
		Factory_sp = Sprite::create("Factory/Bg_Fatory_R.png");
		Factory_sp->setAnchorPoint(Vec2(1, 0.5));
		Factory_sp->setPosition(winSize.width, winSize.height / 2+30);
	}
	else
	{//공장 위치 왼쪽
		Factory_sp = Sprite::create("Factory/Bg_Factory_L.png");
		Factory_sp->setAnchorPoint(Vec2(0, 0.5));
		Factory_sp->setPosition(0, winSize.height / 2 +30);
	}
	

}

void Factory::Create_HpBar()
{
	if (isRight)
	{//공장 위치: 오른쪽
		Hp_Bar_Back = Sprite::create("UI/UI_top_hp_down.png");
		Hp_Bar_Back->setAnchorPoint(Vec2(1, 1));
		Hp_Bar_Back->setPosition(winSize.width-80, winSize.height-20);

		Hp_Bar = Sprite::create("UI/UI_top_hp_up.png");
		Hp_Bar->setAnchorPoint(Vec2(1, 1));
		Hp_Bar->setPosition(winSize.width-80 , winSize.height - 20);


	}
	else
	{//공장 위치 왼쪽
		Hp_Bar_Back = Sprite::create("UI/UI_top_hp_down.png");
		Hp_Bar_Back->setAnchorPoint(Vec2(0, 1));
		Hp_Bar_Back->setPosition(0 + 80, winSize.height - 20);

		Hp_Bar = Sprite::create("UI/UI_top_hp_up.png");
		Hp_Bar->setAnchorPoint(Vec2(0, 1));
		Hp_Bar->setPosition(0 + 80, winSize.height - 20);
	}

	

}

void Factory::Create_HpDownMenu()
{
	if (isRight)
	{
		auto Test_Hpdown_btn = MenuItemImage::create("Wook_Test/Test_Hpdown_1.png", "Wook_Test/Test_Hpdown_2.png", CC_CALLBACK_1(Factory::HpDown, this));

		Test_Hpdown_btn->setPosition(winSize.width,0);
		Test_Hpdown_btn->setAnchorPoint(Vec2(1, 0));
		menu = Menu::create(Test_Hpdown_btn, nullptr);

		menu->setPosition(Vec2::ZERO);
	}
	else
	{
		auto Test_Hpdown_btn = MenuItemImage::create("Wook_Test/Test_Hpdown_1.png", "Wook_Test/Test_Hpdown_2.png", CC_CALLBACK_1(Factory::HpDown, this));

		Test_Hpdown_btn->setPosition(0,0);
		Test_Hpdown_btn->setAnchorPoint(Vec2(0, 0));
		menu = Menu::create(Test_Hpdown_btn, nullptr);

		menu->setPosition(Vec2::ZERO);
	}

}
void Factory::Create_Bubble()
{
	//원
	Circle_bubble_sprite[0] = Hp_Bar_Back = Sprite::create("Bubble/Bubble_40/C1_Blue.png");
	Circle_bubble_sprite[1] = Hp_Bar_Back = Sprite::create("Bubble/Bubble_40/C1_Red.png");
	Circle_bubble_sprite[2] = Hp_Bar_Back = Sprite::create("Bubble/Bubble_40/C1_Yellow.png");
	Circle_bubble_sprite[3] = Hp_Bar_Back = Sprite::create("Bubble/Bubble_40/C2_Blue.png");
	Circle_bubble_sprite[4] = Hp_Bar_Back = Sprite::create("Bubble/Bubble_40/C2_Red.png");
	Circle_bubble_sprite[5] = Hp_Bar_Back = Sprite::create("Bubble/Bubble_40/C2_Yellow.png");
	Circle_bubble_sprite[6] = Hp_Bar_Back = Sprite::create("Factory/BG_Bubble2_40.png");
	Circle_bubble_sprite[7] = Hp_Bar_Back = Sprite::create("Factory/BG_Bubble2_40.png");
	//마름모
	Rhombus_bubble_sprite[0] = Hp_Bar_Back = Sprite::create("Bubble/Bubble_40/R1_Blue.png");
	Rhombus_bubble_sprite[1] = Hp_Bar_Back = Sprite::create("Bubble/Bubble_40/R1_Red.png");
	Rhombus_bubble_sprite[2] = Hp_Bar_Back = Sprite::create("Bubble/Bubble_40/R1_Yellow.png");
	Rhombus_bubble_sprite[3] = Hp_Bar_Back = Sprite::create("Bubble/Bubble_40/R2_Blue.png");
	Rhombus_bubble_sprite[4] = Hp_Bar_Back = Sprite::create("Bubble/Bubble_40/R2_Red.png");
	Rhombus_bubble_sprite[5] = Hp_Bar_Back = Sprite::create("Bubble/Bubble_40/R2_Yellow.png");
	Rhombus_bubble_sprite[6] = Hp_Bar_Back = Sprite::create("Factory/BG_Bubble1_40.png");
	Rhombus_bubble_sprite[7] = Hp_Bar_Back = Sprite::create("Factory/BG_Bubble1_40.png");
	SetPos_Bubble();
}

#pragma endregion


#pragma region 팩토리 관련
void Factory::Factory_Damage_Action()
{
	if (isRight)
	{
		auto First = Spawn::create(ScaleTo::create(0.05, 1.1), MoveBy::create(0.08, Vec2(0, -10)), nullptr);
		auto Second = Spawn::create(ScaleTo::create(0.05, 0.9), MoveBy::create(0.08, Vec2(0, 20)), nullptr);
		auto Third = Spawn::create(ScaleTo::create(0.05, 1), MoveBy::create(0.08, Vec2(0, -10)), nullptr);
		auto Action = Sequence::create(First, Second, Third, nullptr);
		Factory_sp->runAction(Action);


	}
	else
	{
		auto First = Spawn::create(ScaleTo::create(0.05, 1.1), MoveBy::create(0.08, Vec2(0, 10)), nullptr);
		auto Second = Spawn::create(ScaleTo::create(0.05, 0.9), MoveBy::create(0.08, Vec2(0, -20)), nullptr);
		auto Third = Spawn::create(ScaleTo::create(0.05, 1), MoveBy::create(0.08, Vec2(0, 10)), nullptr);
		auto Action = Sequence::create(First, Second, Third, nullptr);
		auto Action1 = Sequence::create(First, Second, Third, nullptr);
		auto Action2 = Sequence::create(First, Second, Third, nullptr);
		Factory_sp->runAction(Action);


	}
	
	
}

void Factory::Factory_Hit_Check(Sprite* _unit)
{
	if (Factory_sp->getBoundingBox().intersectsRect(_unit->getBoundingBox()))
	{//유닛과 충돌
		Factory_Hp_Down();
	}
}

void Factory::Factory_Hp_Down()
{
	if (CurHp <= 0)
	{
		if (isRight)
		{

			GameManager::GetInstance()->Die_Right_Factory();

		}
		else
		{

			
			GameManager::GetInstance()->Die_Left_Factory();
		}

		return;

	}
	Factory_Damage_Action();
	CurHp -= 10;
	if (CurHp <= 0)
		Hp_Bar->setScaleX(0);
	else
		Hp_Bar->setScaleX((float)CurHp / (float)MaxHp);
}
#pragma endregion

#pragma region 버블
int Factory::Change_Key(int _key)
{
	switch (_key)
	{
	case R1_Blue:
		return 0;
	case R1_Red:
		return 1;
	case R1_Yellow:
		return 2;

	case C2_Blue:
	case R2_Blue:
		return 3;
	case R2_Red:
	case C2_Red:
		return 4;
	case C2_Yellow:
	case R2_Yellow:
		return 5;
	}
}

void Factory::Change_Bubble(BUBBLE _Bubble)
{
	Change_Bubble_Setting(_Bubble);
	auto hide = Hide::create();
	auto show = Show::create();
	switch (_Bubble.key)
	{
	case C1_Blue:
	case C1_Red:
	case C1_Yellow:
	case C2_Blue:
	case C2_Red:
	case C2_Yellow:
		_Bubble.key = Change_Key(_Bubble.key);
		//Circle_bubble_sprite[0]->runAction(show);
		if(Circle_bubble.key != None_Circle)
			Circle_bubble_sprite[Circle_bubble.key]->runAction(hide);
		Circle_bubble = _Bubble;
		Circle_bubble_sprite[Circle_bubble.key]->runAction(show);
		break;

	case R1_Blue:
	case R1_Red:
	case R1_Yellow:
	case R2_Blue:
	case R2_Red:
	case R2_Yellow:
		_Bubble.key = Change_Key(_Bubble.key);
		if (Rhombus_bubble.key != None_Rhombus)
			Rhombus_bubble_sprite[Rhombus_bubble.key]->runAction(hide);
		Rhombus_bubble = _Bubble;
		Rhombus_bubble_sprite[Rhombus_bubble.key]->runAction(show);
		break;

	}

	
}
void Factory::Change_Bubble_Setting(BUBBLE _Bubble)
{
	switch (_Bubble.key)
	{
	case C1_Yellow:
	case C2_Yellow:
		CreatUnit_time = CreatUnit_time_Base - _Bubble.SpawnSpeed;
		break;
	}
}
void Factory::SetPos_Bubble()
{
	if (isRight)
	{
		for (int i = 0; i < 7; i++)
		{
			auto action = Hide::create();
			auto action1 = Hide::create();
			Circle_bubble_sprite[i]->setAnchorPoint(Vec2(0.5, 0.5));
			Circle_bubble_sprite[i]->setPosition(Vec2(75, 245));

			Rhombus_bubble_sprite[i]->setAnchorPoint(Vec2(0.5, 0.5));
			Rhombus_bubble_sprite[i]->setPosition(Vec2(155, 245));
			if (i == 6) break;
			Circle_bubble_sprite[i]->runAction(action);
			Rhombus_bubble_sprite[i]->runAction(action1);
		}
	}
	else
	{
		for (int i = 0; i < 7; i++)
		{
			auto action = Hide::create();
			auto action1 = Hide::create();
			Circle_bubble_sprite[i]->setAnchorPoint(Vec2(0.5, 0.5));
			Circle_bubble_sprite[i]->setPosition(Vec2(275, 245));

			Rhombus_bubble_sprite[i]->setAnchorPoint(Vec2(0.5, 0.5));
			Rhombus_bubble_sprite[i]->setPosition( Vec2(195, 245));
			if (i == 6) break;
			Circle_bubble_sprite[i]->runAction(action);
			Rhombus_bubble_sprite[i]->runAction(action1);
		}
	}
	Circle_bubble_sprite[7]->setPosition(Vec2(-3000, -3000));
	Rhombus_bubble_sprite[7]->setPosition(Vec2(-3000, -3000));
}
#pragma endregion


#pragma region 유닛관련
void Factory::Change_CreatUnit_Time(float time)
{
	CreatUnit_time = time * 10;
	CreatUnit_timeCheck = 0;
}

bool Factory::CreatUnit()
{
	CreatUnit_time += 0.1f;
	if (CreatUnit_time >= CreatUnit_timeCheck)
	{
		CreatUnit_time = 0;
		return false;
	}
	return false;
}

#pragma endregion


#pragma region 메뉴 콜백

void Factory::HpDown(Ref* Sender)
{
	if (CurHp <= 0)
	{
		if (isRight)
		{

			GameManager::GetInstance()->Die_Right_Factory();

		}
		else
		{


			GameManager::GetInstance()->Die_Left_Factory();
		}

		return;

	}
	SoundManager::GetInstance()->Play(0);
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

void Factory::Test()
{
	auto show = Show::create();
	Circle_bubble_sprite[0]->runAction(show);

}
