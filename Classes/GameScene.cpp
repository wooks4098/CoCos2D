#include "HelloWorldScene.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "Factory.h"

using namespace cocos2d;


	//모든 유닛 저장
Vector<Unit*> unitsL;
Vector<Unit*> unitsR;

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

	unitsL.clear();
	unitsR.clear();

	bitCoinL = 150;
	bitCoinR = 150;
	bubbleCostL = 50;
	bubbleCostR = 50;
	unitCostL = 100;
	unitCostR = 100;
	coinAmount = 50;

	Create_BackGround();
	Creat_Factory();


	//스케줄 등록
	this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&GameScene::Update));
	this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&GameScene::Factory_Right_CreatUnitCheck), 0.1f);
	this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&GameScene::Factory_Left_CreatUnitCheck), 0.1f);	
	this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&GameScene::OneTwoThreeFourBubbleBubbleLeft));
	this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&GameScene::OneTwoThreeFourBubbleBubbleRight));
	this->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&GameScene::GetCoinInTime),1.0f);

	
	return true;
}


void GameScene::Creat_Factory()
{
	SoundManager::GetInstance()->Play(BackGround_1);

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
	
	//llllllllllllllllllllllllllllllll
	UI_Left_bottom_Info = Sprite::create("UI/UI_bottom_Info_Left.png");
	UI_Left_bottom_Info->setAnchorPoint(Vec2(0, 0));
	UI_Left_bottom_Info->setPosition(0, 0);
	this->addChild(UI_Left_bottom_Info);

	UI_Left_bottom_Bubble = MenuItemImage::create("UI/UI_bottom_Bubble.png", "UI/UI_bottom_Bubble1.png", CC_CALLBACK_1(GameScene::ClickToCreateBubble1, this, 1, false));
	UI_Left_bottom_Bubble->setAnchorPoint(Vec2(0, 0));
	UI_Left_bottom_Bubble->setPosition(UI_Left_bottom_Info->getContentSize().width, 0);
	
	UI_Left_bottom_Unit = MenuItemImage::create("UI/UI_bottom_Unit.png", "UI/UI_bottom_Unit1.png", CC_CALLBACK_1(GameScene::UnitUpgraid, this,FACTORY_LEFT));
	UI_Left_bottom_Unit->setAnchorPoint(Vec2(0, 0));
	UI_Left_bottom_Unit->setPosition(UI_Left_bottom_Info->getContentSize().width, UI_Left_bottom_Bubble->getContentSize().height);

	UI_Left_bottom_Inven = Sprite::create("UI/UI_bottom_Inven.png");
	UI_Left_bottom_Inven->setAnchorPoint(Vec2(0, 0));
	UI_Left_bottom_Inven->setPosition(UI_Left_bottom_Info->getContentSize().width+ UI_Left_bottom_Bubble->getContentSize().width, 0);
	this->addChild(UI_Left_bottom_Inven);

	UI_Left_bottom_Delet = Sprite::create("UI/UI_bottom_Delet.png");
	UI_Left_bottom_Delet->setAnchorPoint(Vec2(0, 0));
	UI_Left_bottom_Delet->setPosition(UI_Left_bottom_Inven->getContentSize().width+ UI_Left_bottom_Info->getContentSize().width + UI_Left_bottom_Bubble->getContentSize().width, 0);
	this->addChild(UI_Left_bottom_Delet);

	Lcoin = Label::createWithTTF("333","fonts/Marker Felt.ttf", 28);
	Lcoin->setString(StringUtils::format("%d", bitCoinL));
	Lcoin->setPosition(Vec2(71, 73));
	Lcoin->setColor(Color3B::BLACK);
	this->addChild(Lcoin);

	auto menu1 = Menu::create(UI_Left_bottom_Bubble, UI_Left_bottom_Unit, nullptr);
	this->addChild(menu1);
	menu1->setPosition(Vec2::ZERO);

	Lbitcoincost = Label::createWithTTF("333", "fonts/Marker Felt.ttf", 24);
	Lbitcoincost->setString(StringUtils::format("%d", bubbleCostL));
	Lbitcoincost->setPosition(Vec2(335, 20));
	Lbitcoincost->setColor(Color3B::BLACK);
	this->addChild(Lbitcoincost);

	LbitcoincostU = Label::createWithTTF("333", "fonts/Marker Felt.ttf", 24);
	LbitcoincostU->setString(StringUtils::format("%d", unitCostL));
	LbitcoincostU->setPosition(Vec2(335, 50));
	LbitcoincostU->setColor(Color3B::BLACK);
	this->addChild(LbitcoincostU);

	//rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
	UI_Right_bottom_Info = Sprite::create("UI/UI_bottom_Info_Right.png");
	UI_Right_bottom_Info->setAnchorPoint(Vec2(1, 0));
	UI_Right_bottom_Info->setPosition(winSize.width, 0);
	this->addChild(UI_Right_bottom_Info);
	
	UI_Right_bottom_Bubble = MenuItemImage::create("UI/UI_bottom_Bubble.png", "UI/UI_bottom_Bubble1.png", CC_CALLBACK_1(GameScene::ClickToCreateBubble1, this, 1, true));
	UI_Right_bottom_Bubble->setAnchorPoint(Vec2(1, 0));
	UI_Right_bottom_Bubble->setPosition(winSize.width - UI_Right_bottom_Info->getContentSize().width, 0);

	UI_Right_bottom_Unit = MenuItemImage::create("UI/UI_bottom_Unit.png", "UI/UI_bottom_Unit1.png", CC_CALLBACK_1(GameScene::UnitUpgraid, this, FACTORY_RIGHT));
	UI_Right_bottom_Unit->setAnchorPoint(Vec2(1, 0));
	UI_Right_bottom_Unit->setPosition(winSize.width - UI_Right_bottom_Info->getContentSize().width, UI_Right_bottom_Bubble->getContentSize().height);

	UI_Right_bottom_Inven = Sprite::create("UI/UI_bottom_Inven.png");
	UI_Right_bottom_Inven->setAnchorPoint(Vec2(1, 0));
	UI_Right_bottom_Inven->setPosition(winSize.width - UI_Right_bottom_Info->getContentSize().width - UI_Right_bottom_Bubble->getContentSize().width, 0);
	this->addChild(UI_Right_bottom_Inven);

	UI_Right_bottom_Delet = Sprite::create("UI/UI_bottom_Delet.png");
	UI_Right_bottom_Delet->setAnchorPoint(Vec2(1, 0));
	UI_Right_bottom_Delet->setPosition(winSize.width - UI_Right_bottom_Inven->getContentSize().width- UI_Right_bottom_Info->getContentSize().width - UI_Right_bottom_Bubble->getContentSize().width, 0);
	this->addChild(UI_Right_bottom_Delet);

	Rcoin = Label::createWithTTF("333", "fonts/Marker Felt.ttf", 28);
	Rcoin->setString(StringUtils::format("%d", bitCoinR));
	Rcoin->setPosition(Vec2(winSize.width- 75, 73));
	Rcoin->setColor(Color3B::BLACK);
	this->addChild(Rcoin);

	auto menu2 = Menu::create(UI_Right_bottom_Bubble, UI_Right_bottom_Unit, nullptr);
	this->addChild(menu2);
	menu2->setPosition(Vec2::ZERO);

	Rbitcoincost = Label::createWithTTF("333", "fonts/Marker Felt.ttf", 24);
	Rbitcoincost->setString(StringUtils::format("%d", bubbleCostR));
	Rbitcoincost->setPosition(Vec2(winSize.width - 332, 20));
	Rbitcoincost->setColor(Color3B::BLACK);
	this->addChild(Rbitcoincost);


	RbitcoincostU = Label::createWithTTF("333", "fonts/Marker Felt.ttf", 24);
	RbitcoincostU->setString(StringUtils::format("%d", unitCostR));
	RbitcoincostU->setPosition(Vec2(winSize.width - 332, 50));
	RbitcoincostU->setColor(Color3B::BLACK);
	this->addChild(RbitcoincostU);

	//인벤칸 초기화
	for (int i = 0; i < 4; i++)
	{
		invenPos_Left[i].x = UI_Left_bottom_Info->getContentSize().width + UI_Left_bottom_Bubble->getContentSize().width + 43 + i * 68;
		invenPos_Left[i + 4].x = UI_Left_bottom_Info->getContentSize().width + UI_Left_bottom_Bubble->getContentSize().width + 43 + i * 68;
		invenPos_Left[i].y = UI_Right_bottom_Bubble->getContentSize().height + 35;
		invenPos_Left[i + 4].y = UI_Right_bottom_Bubble->getContentSize().height - 33;

		invenPos_Right[3-i].x = winSize.width - (UI_Left_bottom_Info->getContentSize().width + UI_Left_bottom_Bubble->getContentSize().width + 43 + i * 68);
		invenPos_Right[3-i + 4].x = winSize.width - (UI_Left_bottom_Info->getContentSize().width + UI_Left_bottom_Bubble->getContentSize().width + 43 + i * 68);
		invenPos_Right[i].y = UI_Right_bottom_Bubble->getContentSize().height + 35;
		invenPos_Right[i + 4].y = UI_Right_bottom_Bubble->getContentSize().height - 33;
	}
}
void GameScene::UnitUpgraid(Ref* pSender, int dir)
{
	factory[dir].UnitUpgraid();
	if (dir == FACTORY_RIGHT)//r
	{
		bitCoinR -= unitCostR;
		unitCostR += 20;
		Rbitcoincost->setString(StringUtils::format("%d", bubbleCostR));
		Rcoin->setString(StringUtils::format("%d", bitCoinR));
	}
	else if(dir == FACTORY_LEFT)
	{
		bitCoinL -= unitCostL;
		unitCostL += 20;
		Lbitcoincost->setString(StringUtils::format("%d", bubbleCostL));
		Lcoin->setString(StringUtils::format("%d", bitCoinL));
	}
}
void GameScene::Creat_End_Menu(bool isRightWin)
{
	SoundManager::GetInstance()->Play(UI_End);
	stopAllUnit();
	isEnd = true;
	if (isRightWin)
	{
		end_Image = Sprite::create("UI/GameEnd/WUI_Green.png");
		end_Image->setAnchorPoint(Vec2(0.5, 0.5));
		end_Image->setPosition(winSize.width/2, winSize.height/2);
		this->addChild(end_Image);
	}
	else
	{
		end_Image = Sprite::create("UI/GameEnd/WUI_Red.png");
		end_Image->setAnchorPoint(Vec2(0.5, 0.5));
		end_Image->setPosition(winSize.width / 2, winSize.height / 2);
		this->addChild(end_Image);
	}
	auto _Play = cocos2d::MenuItemImage::create("UI/GameEnd/WUI_RB00.png", "UI/GameEnd/WUI_RB0.png", CC_CALLBACK_1(GameScene::go_Play, this));
	_Play->setAnchorPoint(Vec2(1, 0.7));

	auto _Menu = cocos2d::MenuItemImage::create("UI/GameEnd/WUI_HB00.png", "UI/GameEnd/WUI_HB0.png", CC_CALLBACK_1(GameScene::go_Menu, this));
	_Menu->setAnchorPoint(Vec2(0, 0.7));


	End_menu = Menu::create(_Play, _Menu, nullptr);
	End_menu->setAnchorPoint(Vec2(0, 0));
	End_menu->setPosition(Vec2(winSize.width/2, 230));
	this->addChild(End_menu);


	
}

void GameScene::GetCoinInTime(float f)
{
	bitCoinL += coinAmount;
	bitCoinR += coinAmount;
	Rcoin->setString(StringUtils::format("%d", bitCoinR));
	Lcoin->setString(StringUtils::format("%d", bitCoinL));

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
		randnum = R1_Yellow;

		switch (randnum)
		{
		case C1_Blue:
			val.Defense = 10;
			val.key = 0;
			break;
		case C1_Red:
			val.Hp = 20;
			val.key = 1;
			break;
		case C1_Yellow:
			val.SpawnSpeed = 1.1f;
			val.key = 2;
			break;
		case R1_Blue:
			val.Damage = 20;
			val.key = 3;
			break;
		case R1_Red:
			val.AttackSpeed = 0.5f;
			val.key = 4;
			break;
		case R1_Yellow:
			val.MoveSpeed = 50;
			val.key = 5;
			break;
		default:
			break;
		}
	}
	else if (lev == 2)
	{
		randnum = (rand() % 6) + 6;
		randnum = R2_Yellow;

		switch (randnum)
		{
		case C2_Blue:
			val.Defense = 15;
			val.key = 6;
			break;
		case C2_Red:
			val.Hp = 35;
			val.key = 7;
			break;
		case C2_Yellow:
			val.SpawnSpeed = 1.2f;
			val.key = 8;
			break;
		case R2_Blue:
			val.Damage = 30;
			val.key = 9;
			break;
		case R2_Red:
			val.AttackSpeed = 1;
			val.key = 10;
			break;
		case R2_Yellow:
			val.MoveSpeed = 75;
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
	if (isRight)
	{
		if (bubblesRight.size() < 8 && (bitCoinR > bubbleCostR || lev==2))
		{
			Bubble* bb = Bubble::create();
			bubblesRight.pushBack(bb->BubbleCreate(GetPP(lev)));
			//Bubble* a;
			//bubblesRight.pushBack(bubblesRight.at(bubblesRight.size())->BubbleCreate(GetPP(lev)));
			//bb = bb->BubbleCreate();
			//bubblesRight.pushBack(bb);
			//bubblesRight.back() = bubblesLeft.back()->BubbleCreate(GetPP(lev));
			for (int i = 0; i < 8; i++)
			{
				if (!invenPos_Right[i].isFull)
				{
					invenPos_Right[i].isFull = true;
					bubblesRight.back()->SetPosNum(i);
					bubblesRight.back()->setPosition(Vec2(invenPos_Right[i].x, invenPos_Right[i].y));
					
					if (lev == 1)
					{
						bitCoinR -= bubbleCostR;
						bubbleCostR += 10;
						Rbitcoincost->setString(StringUtils::format("%d", bubbleCostR));
						Rcoin->setString(StringUtils::format("%d", bitCoinR));
					}
					break;
				}
			}
			this->addChild(bubblesRight.back());
		}
	}
	else
	{
		if (bubblesLeft.size() < 8 && (bitCoinL > bubbleCostL||lev==2))
		{
			Bubble* bb = Bubble::create();
			bubblesLeft.pushBack(bb->BubbleCreate(GetPP(lev)));
			for (int i = 0; i < 8; i++)
			{
				if (!invenPos_Left[i].isFull)
				{
					invenPos_Left[i].isFull = true;
					bubblesLeft.back()->SetPosNum(i);
					bubblesLeft.back()->setPosition(Vec2(invenPos_Left[i].x, invenPos_Left[i].y));
					if (lev == 1)
					{
						bitCoinL -= bubbleCostL;
						bubbleCostL += 10;
						Lbitcoincost->setString(StringUtils::format("%d", bubbleCostL));
						Lcoin->setString(StringUtils::format("%d", bitCoinL));
					}
					break;
				}
			}
			this->addChild(bubblesLeft.back());
		}
	}
}
#pragma region 스케줄

void GameScene::Update(float f)
{
	if (GameManager::GetInstance()->Return_isRightFactory_Die()&& !isEndOpen)
	{
		//오른쪽 팩토리 사망
		Creat_End_Menu(false);
		isEndOpen = true;
	}
	if (GameManager::GetInstance()->Return_isLeftFactory_Die()&& !isEndOpen)
	{
		//왼쪽 팩토리 사망
		Creat_End_Menu(true);
		isEndOpen = true;
	}
}

void GameScene::Factory_Right_CreatUnitCheck(float f)
{
	if (factory[FACTORY_RIGHT].CreatUnit()&&!isEnd)
	{
		BUBBLE _bubble = factory[FACTORY_RIGHT].return_bubble();
		/*_bubble.AttackSpeed;
		_bubble.Damage;
		_bubble.Defense;
		_bubble.Hp;
		_bubble.MoveSpeed;*/

		Unit* unit = RightUnit::createUnit(&factory[FACTORY_RIGHT], &factory[FACTORY_LEFT], _bubble);
		unit->initUnit(_bubble);
		unit->unitNumber = GameManager::GetInstance()->totalUnitNumR;
		GameManager::GetInstance()->totalUnitNumR++;
		unitsR.pushBack(unit);
		this->addChild(unit);
		unit->moveUnit();
	}
}

void GameScene::Factory_Left_CreatUnitCheck(float f)
{
	if (factory[FACTORY_LEFT].CreatUnit() && !isEnd)
	{
		BUBBLE _bubble = factory[FACTORY_LEFT].return_bubble();
		/*_bubble.AttackSpeed;
		_bubble.Damage;
		_bubble.Defense;
		_bubble.Hp;
		_bubble.MoveSpeed;*/

		Unit* unit = LeftUnit::createUnit(&factory[FACTORY_LEFT], &factory[FACTORY_RIGHT], _bubble);
		unit->initUnit(_bubble);
		unit->unitNumber = GameManager::GetInstance()->totalUnitNumL;
		GameManager::GetInstance()->totalUnitNumL++;
		unitsL.pushBack(unit);
		this->addChild(unit);
		unit->moveUnit();
	}
}

void GameScene::OneTwoThreeFourBubbleBubbleRight(float f)
{
	for (int i = 0; i < bubblesRight.size(); i++)
	{
		if (bubblesRight.at(i)->isMove())//움직이고 있다면 충돌처리를 하지 않는다.
		{
			return;
		}
	}
	//충돌철이//첫 생성 시 겹쳐서 생성되면 바로 합쳐진다...
	if (bubblesRight.size() >= 2)
	{
		for (int i = 0; i < bubblesRight.size(); i++)
		{
			for (int j = i + 1; j < bubblesRight.size(); j++)
			{
				if (bubblesRight.at(i)->getBoundingBox().intersectsRect(bubblesRight.at(j)->getBoundingBox()))
				{
					if (bubblesRight.at(i)->BubbleStat_rt().key <= 5 && bubblesRight.at(i)->BubbleStat_rt().key == bubblesRight.at(j)->BubbleStat_rt().key)
					{
						auto removebb=Bubble::create();
						log("R C Check");
						invenPos_Right[bubblesRight.at(i)->GetPosNum()].isFull = false;
						
						removebb = bubblesRight.at(i);
						this->removeChild(bubblesRight.at(i));

						//bubblesRight[i]->removeFromParentAndCleanup(true);

						bubblesRight.erase(bubblesRight.begin() + i);
						if (i != j)
						{
							invenPos_Right[bubblesRight.at(j - 1)->GetPosNum()].isFull = false;
							
							removebb = bubblesRight.at(j - 1);
							this->removeChild(bubblesRight.at(j - 1));
							//bubblesRight[j - 1]->removeFromParentAndCleanup(true);
							bubblesRight.erase(bubblesRight.begin() + j - 1);
						}
						//new 버블 생성 코드
						//if(bubblesTest.era)

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
		auto removebb = Bubble::create();

		if (bubblesRight.at(i)->getBoundingBox().intersectsRect(factory[FACTORY_RIGHT].return_Factory_Sp()->getBoundingBox()))
		{
			factory[FACTORY_RIGHT].Change_Bubble(bubblesRight.at(i)->BubbleStat_rt());
			invenPos_Right[bubblesRight.at(i)->GetPosNum()].isFull = false;
			
			//bubblesRight[i]->removeFromParentAndCleanup(true);
			removebb = bubblesRight.at(i);
			this->removeChild(bubblesRight.at(i));

			bubblesRight.erase(bubblesRight.begin() + i);
			break;
		}

		if (bubblesRight.at(i)->getBoundingBox().intersectsRect(UI_Right_bottom_Delet->getBoundingBox()))
		{
			bitCoinR += bubbleCostR * 0.5f - 10;
			Rcoin->setString(StringUtils::format("%d", bitCoinR));
			invenPos_Right[bubblesRight.at(i)->GetPosNum()].isFull = false;

			//bubblesRight[i]->removeFromParentAndCleanup(true);
			removebb = bubblesRight.at(i);
			this->removeChild(bubblesRight.at(i));

			bubblesRight.erase(bubblesRight.begin() + i);
		}
		else
		{
			bubblesRight.at(i)->setPosition(Vec2(invenPos_Right[bubblesRight.at(i)->GetPosNum()].x, invenPos_Right[bubblesRight.at(i)->GetPosNum()].y));
		}
	}
}
void GameScene::OneTwoThreeFourBubbleBubbleLeft(float f)
{
	for (int i = 0; i < bubblesLeft.size(); i++)
	{
		if (bubblesLeft.at(i)->isMove())//움직이고 있다면 충돌처리를 하지 않는다.
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
				if (bubblesLeft.at(i)->getBoundingBox().intersectsRect(bubblesLeft.at(j)->getBoundingBox()))
				{
					if (bubblesLeft.at(i)->BubbleStat_rt().key <= 5 && bubblesLeft.at(i)->BubbleStat_rt().key == bubblesLeft.at(j)->BubbleStat_rt().key)
					{
						log("L C Check");
						invenPos_Left[bubblesLeft.at(i)->GetPosNum()].isFull = false;
						bubblesLeft.at(i)->removeFromParentAndCleanup(true);
						bubblesLeft.erase(bubblesLeft.begin() + i);
						if (i != j)
						{
							invenPos_Left[bubblesLeft.at(j-1)->GetPosNum()].isFull = false;
							bubblesLeft.at(j-1)->removeFromParentAndCleanup(true);
							bubblesLeft.erase(bubblesLeft.begin() + j - 1);
						}
						//new 버블 생성 코드
						ClickToCreateBubble1(this, 2, false);
						return;
					}
				}
			}
		}
	}
	
	//left
	for (int i = 0; i < bubblesLeft.size(); i++)
	{
		if (bubblesLeft.at(i)->getBoundingBox().intersectsRect(factory[FACTORY_LEFT].return_Factory_Sp()->getBoundingBox()))
		{
			factory[FACTORY_LEFT].Change_Bubble(bubblesLeft.at(i)->BubbleStat_rt());
			invenPos_Left[bubblesLeft.at(i)->GetPosNum()].isFull = false;
			bubblesLeft.at(i)->removeFromParentAndCleanup(true);
			bubblesLeft.erase(bubblesLeft.begin() + i);
			break;
		}
	
		if (bubblesLeft.at(i)->getBoundingBox().intersectsRect(UI_Left_bottom_Delet->getBoundingBox()))
		{
			bitCoinL += bubbleCostL * 0.5f - 10;
			Lcoin->setString(StringUtils::format("%d", bitCoinL));
			invenPos_Left[bubblesLeft.at(i)->GetPosNum()].isFull = false;
			bubblesLeft.at(i)->removeFromParentAndCleanup(true);
			bubblesLeft.erase(bubblesLeft.begin() + i);
		}
		else
		{
			bubblesLeft.at(i)->setPosition(Vec2(invenPos_Left[bubblesLeft.at(i)->GetPosNum()].x, invenPos_Left[bubblesLeft.at(i)->GetPosNum()].y));
		}
	}
}
#pragma endregion

void GameScene::go_Menu(Ref* pSender)
{
	GameManager::GetInstance()->Reset();
	//this->removeAllChildren();
	auto _MenuScene = MenuScene::createScene();
	Director::getInstance()->replaceScene(_MenuScene);

}

void GameScene::go_Play(Ref* pSender)
{
	GameManager::GetInstance()->Reset();

	//this->removeAllChildren();
	auto _GameScene = GameScene::createScene();
	Director::getInstance()->replaceScene(_GameScene);


}

#pragma region unit
void GameScene::stopAllUnit()
{
	for (Unit* unitL : unitsL)
	{
		unitL->unscheduleUpdate();
		unitL->stopAllActions();
	}

	for (Unit* unitR : unitsR)
	{
		unitR->unscheduleUpdate();
		unitR->stopAllActions();
	}
}
#pragma endregion