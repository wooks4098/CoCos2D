
#include "HelloWorldScene.h"
#include "GameScene .h"

using namespace cocos2d;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
		return false;
	auto wlayer = LayerColor::create(Color4B::WHITE);
	addChild(wlayer);
	winSize = Director::getInstance()->getWinSize(); //화면의 사이즈 구하기

	bitCoin = 100;

	Create_BackGround();
	Creat_Factory();

	DeleteZoneL = Sprite::create("UI/UI_bottom_Delet.png");
	DeleteZoneR = Sprite::create("UI/UI_bottom_Delet.png");
	DeleteZoneL->setPosition(Vec2(200, 100));
	this->addChild(DeleteZoneL);

#pragma region menu
	auto m_3 = MenuItemImage::create("btn-play-normal.png", "btn-play-selected.png", CC_CALLBACK_1(GameScene::ClickToCreateBubble1, this, 1, true));
	auto m_4 = MenuItemImage::create("end1.PNG", "end2.PNG", CC_CALLBACK_1(GameScene::ClickToCreateBubble1, this, 1, false));
	m_3->setTag(1);
	m_4->setTag(2);
	auto menu1 = Menu::create(m_3, m_4, nullptr);
	m_3->setPosition(Vec2(480, 320));
	m_3->setAnchorPoint(Vec2(1, 1));
	m_4->setPosition(Vec2(0, 320));
	m_4->setAnchorPoint(Vec2(0, 1));
	this->addChild(menu1);
	menu1->setPosition(Vec2::ZERO);
#pragma endregion


	//스케줄 등록
	this->schedule(schedule_selector(GameScene::Factory_Right_CreatUnitCheck), 0.1f);
	this->schedule(schedule_selector(GameScene::Factory_Left_CreatUnitCheck), 0.1f);
	this->schedule(schedule_selector(GameScene::Update));
	this->schedule(schedule_selector(GameScene::OneTwoThreeFourBubbleBubbleLeft));
	this->schedule(schedule_selector(GameScene::OneTwoThreeFourBubbleBubbleRight));
	return true;
}


void GameScene::Creat_Factory()
{
	//팩토리 생성
	factory[FACTORY_RIGHT].Create(FACTORY_RIGHT);

	factory[FACTORY_LEFT].Create(FACTORY_LEFT);
	//팩토리 등록
	this->addChild(factory[FACTORY_RIGHT].return_Menu());
	this->addChild(factory[FACTORY_RIGHT].return_HpBar_Back());
	this->addChild(factory[FACTORY_RIGHT].return_HpBar());
	this->addChild(factory[FACTORY_RIGHT].return_Factory_Sp());

	this->addChild(factory[FACTORY_LEFT].return_Menu());
	this->addChild(factory[FACTORY_LEFT].return_HpBar_Back());
	this->addChild(factory[FACTORY_LEFT].return_HpBar());
	this->addChild(factory[FACTORY_LEFT].return_Factory_Sp());
	//버블 등록
	for(int i = 6; i>0-1; i--)
	{
		factory[FACTORY_RIGHT].return_Factory_Sp()->addChild(factory[FACTORY_RIGHT].return_Circle_bubble(i));
		factory[FACTORY_RIGHT].return_Factory_Sp()->addChild(factory[FACTORY_RIGHT].return_Rhombus_bubble(i));
		factory[FACTORY_LEFT].return_Factory_Sp()->addChild(factory[FACTORY_LEFT].return_Circle_bubble(i));
		factory[FACTORY_LEFT].return_Factory_Sp()->addChild(factory[FACTORY_LEFT].return_Rhombus_bubble(i));
	}
}
void GameScene::Create_BackGround()
{
	Factory_Back = Sprite::create("Factory/BG.png");
	Factory_Back->setAnchorPoint(Vec2(0, 0.5));
	Factory_Back->setPosition(0, winSize.height / 2);
	this->addChild(Factory_Back);

	UI_Hp_top = Sprite::create("UI/UI_top.png");
	UI_Hp_top->setAnchorPoint(Vec2(0, 1));
	UI_Hp_top->setPosition(0, winSize.height);
	this->addChild(UI_Hp_top);
	UI_Left_bottom_Info = Sprite::create("UI/UI_bottom_Info_Left.png");
	UI_Left_bottom_Info->setAnchorPoint(Vec2(0, 0));
	UI_Left_bottom_Info->setPosition(0, 0);
	this->addChild(UI_Left_bottom_Info);

	UI_Left_bottom_Inven = Sprite::create("UI/UI_bottom_Inventory.png");
	UI_Left_bottom_Inven->setAnchorPoint(Vec2(0, 0));
	UI_Left_bottom_Inven->setPosition(UI_Left_bottom_Info->getContentSize().width, 0);
	this->addChild(UI_Left_bottom_Inven);

	UI_Left_bottom_Delet = Sprite::create("UI/UI_bottom_Delet.png");
	UI_Left_bottom_Delet->setAnchorPoint(Vec2(0, 0));
	UI_Left_bottom_Delet->setPosition(UI_Left_bottom_Inven->getContentSize().width, 0);
	this->addChild(UI_Left_bottom_Delet);

	UI_Right_bottom_Info = Sprite::create("UI/UI_bottom_Info_Right.png");
	UI_Right_bottom_Info->setAnchorPoint(Vec2(1, 0));
	UI_Right_bottom_Info->setPosition(winSize.width, 0);
	this->addChild(UI_Right_bottom_Info);

	UI_Right_bottom_Inven = Sprite::create("UI/UI_bottom_Inventory.png");
	UI_Right_bottom_Inven->setAnchorPoint(Vec2(1, 0));
	UI_Right_bottom_Inven->setPosition(winSize.width - UI_Right_bottom_Info->getContentSize().width, 0);
	this->addChild(UI_Right_bottom_Inven);

	UI_Right_bottom_Delet = Sprite::create("UI/UI_bottom_Delet.png");
	UI_Right_bottom_Delet->setAnchorPoint(Vec2(1, 0));
	UI_Right_bottom_Delet->setPosition(winSize.width - UI_Right_bottom_Inven->getContentSize().width, 0);
	this->addChild(UI_Right_bottom_Delet);
}

BUBBLE GameScene::GetPP(int lev)
{

	val.Hp = 0;
	val.Defense = 0;
	val.Damage = 0;
	val.AttackSpeed = 0;
	val.MoveSpeed = 0;
	val.SpawnSpeed = 0;


	if (lev == 1)
	{
		randnum = rand() % 6;
		switch (randnum)
		{
		case C1_Blue:
			val.Defense = 5;
			val.key = 0;
			break;
		case C1_Red:
			val.Hp = 5;
			val.key = 1;
			break;
		case C1_Yellow:
			val.SpawnSpeed = -0.1f;
			val.key = 2;
			break;
		case R1_Blue:
			val.Damage = 2;
			val.key = 3;
			break;
		case R1_Red:
			val.AttackSpeed = 0.5f;
			val.key = 4;
			break;
		case R1_Yellow:
			val.MoveSpeed = 5;
			val.key = 5;
			break;
		default:
			break;
		}
	}
	else if (lev == 2)
	{
		randnum = (rand() % 6) + 6;

		switch (randnum)
		{
		case C2_Blue:
			val.Defense = 10;
			val.key = 6;
			break;
		case C2_Red:
			val.Hp = 10;
			val.key = 7;
			break;
		case C2_Yellow:
			val.SpawnSpeed = -0.3f;
			val.key = 8;
			break;
		case R2_Blue:
			val.Damage = 3;
			val.key = 9;
			break;
		case R2_Red:
			val.AttackSpeed = 1;
			val.key = 10;
			break;
		case R2_Yellow:
			val.MoveSpeed = 15;
			val.key = 11;
			break;
		default:
			break;
		}
	}

	//val.Hp = 100 + addval.Hp;
	//val.Defense = 5 + addval.Defense;
	//val.Damage = 10 + addval.Damage;
	//val.AttackSpeed = 1.0f + addval.AttackSpeed;
	//val.MoveSpeed = 5 + addval.MoveSpeed;
 //   val.Spawn_time = 3 + addval.Spawn_time;

	return val;
}
void GameScene::ClickToCreateBubble1(Ref* pSender, int lev, bool isRight)
{
	//bubbles.push_back(new Bubble);
	//bubbles.back()->BubbleCreate(GetPP(1));
	//bubbles.back()->setPr(10);
	//bubbles.back()->setPrWiththis(false);
	//this->addChild(bubbles.back()->Bubble_rt());
	bubblesLeft.push_back(new Bubble);
	bubblesLeft.back() = bubblesLeft.back()->BubbleCreate(GetPP(lev));
	this->addChild(bubblesLeft.back());
}
#pragma region 스케줄

void GameScene::Update(float f)
{

}

void GameScene::Factory_Right_CreatUnitCheck(float f)
{
	//factory[FACTORY_RIGHT].CreatUnit();
}

void GameScene::Factory_Left_CreatUnitCheck(float f)
{
	//factory[FACTORY_LEFT].CreatUnit();
}
void GameScene::OneTwoThreeFourBubbleBubbleRight(float f)
{
	for (int i = 0; i < bubblesRight.size(); i++)
	{
		if (bubblesRight[i]->isMove())//움직이고 있다면 충돌처리를 하지 않는다.
		{
			return;
		}
	}
	
	//right
	if (bubblesRight.size() >= 2)
	{
		for (int i = 0; i < bubblesRight.size(); i++)
		{
			for (int j = i + 1; j < bubblesRight.size(); j++)
			{
				if (bubblesRight[i]->getBoundingBox().intersectsRect(bubblesRight[j]->getBoundingBox()))
				{
					if (bubblesRight[i]->BubbleStat_rt().key <= 5 && bubblesRight[i]->BubbleStat_rt().key == bubblesRight[j]->BubbleStat_rt().key)
					{
						log("R C Check");
						bubblesRight[i]->removeFromParentAndCleanup(true);
						bubblesRight.erase(bubblesRight.begin() + i);
						if (i != j)
						{
							bubblesRight[j - 1]->removeFromParentAndCleanup(true);
							bubblesRight.erase(bubblesRight.begin() + j - 1);
						}
						//new 버블 생성 코드
						ClickToCreateBubble1(this, 2, true);
						return;
					}
				}
			}
		}
	}

	//right
	for (int i = 0; i < bubblesRight.size(); i++)
	{
		if (bubblesRight[i]->getBoundingBox().intersectsRect(factory[FACTORY_RIGHT].return_Factory_Sp()->getBoundingBox()))
		{
			factory[FACTORY_RIGHT].Change_Bubble(bubblesRight[i]->BubbleStat_rt());
			bubblesRight[i]->removeFromParentAndCleanup(true);
			bubblesRight.erase(bubblesRight.begin() + i);
			break;
		}
		if (bubblesRight[i]->getBoundingBox().intersectsRect(DeleteZoneL->getBoundingBox()))
		{
			//coin++
			bubblesRight[i]->removeFromParentAndCleanup(true);
			bubblesRight.erase(bubblesRight.begin() + i);
		}
	}
}
void GameScene::OneTwoThreeFourBubbleBubbleLeft(float f)
{
	for (int i = 0; i < bubblesLeft.size(); i++)
	{
		if (bubblesLeft[i]->isMove())//움직이고 있다면 충돌처리를 하지 않는다.
		{
			return;
		}
	}
	//충돌철이//첫 생성 시 겹쳐서 생성되면 바로 합쳐진다...
	if (bubblesLeft.size() >= 2)
	{
		for (int i = 0; i < bubblesLeft.size(); i++)
		{
			for (int j = i + 1; j < bubblesLeft.size(); j++)
			{
				if (bubblesLeft[i]->getBoundingBox().intersectsRect(bubblesLeft[j]->getBoundingBox()))
				{
					if (bubblesLeft[i]->BubbleStat_rt().key <= 5 && bubblesLeft[i]->BubbleStat_rt().key == bubblesLeft[j]->BubbleStat_rt().key)
					{
						log("L C Check");
						bubblesLeft[i]->removeFromParentAndCleanup(true);
						bubblesLeft.erase(bubblesLeft.begin() + i);
						if (i != j)
						{
							bubblesLeft[j - 1]->removeFromParentAndCleanup(true);
							bubblesLeft.erase(bubblesLeft.begin() + j - 1);
						}
						//new 버블 생성 코드
						ClickToCreateBubble1(this, 2, true);
						return;
					}
				}
			}
		}
	}
	
	//left
	for (int i = 0; i < bubblesLeft.size(); i++)
	{
		if (bubblesLeft[i]->getBoundingBox().intersectsRect(factory[FACTORY_RIGHT].return_Factory_Sp()->getBoundingBox()))
		{
			factory[FACTORY_RIGHT].Change_Bubble(bubblesLeft[i]->BubbleStat_rt());
			bubblesLeft[i]->removeFromParentAndCleanup(true);
			bubblesLeft.erase(bubblesLeft.begin() + i);
			break;
		}
		if (bubblesLeft[i]->getBoundingBox().intersectsRect(DeleteZoneL->getBoundingBox()))
		{
			//coin++
			bubblesLeft[i]->removeFromParentAndCleanup(true);
			bubblesLeft.erase(bubblesLeft.begin() + i);
		}
	}
//	else if()
}
#pragma endregion

