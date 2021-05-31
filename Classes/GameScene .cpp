
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
	winSize = Director::getInstance()->getWinSize(); //ȭ���� ������ ���ϱ�

	bitCoinL = 150;
	bitCoinR = 150;
	bubbleCostL = 50;
	bubbleCostR = 50;
	coinAmount = 5;

	Create_BackGround();
	Creat_Factory();

#pragma region menu
	auto m_3 = MenuItemImage::create("UI/UI_bottom_Bubble.png", "UI/UI_bottom_Bubble1.png", CC_CALLBACK_1(GameScene::ClickToCreateBubble1, this, 1, true));
	auto m_4 = MenuItemImage::create("UI/UI_bottom_Bubble.png", "UI/UI_bottom_Bubble1.png", CC_CALLBACK_1(GameScene::ClickToCreateBubble1, this, 1, false));
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


	//������ ���
	this->schedule(schedule_selector(GameScene::Factory_Right_CreatUnitCheck), 0.1f);
	this->schedule(schedule_selector(GameScene::Factory_Left_CreatUnitCheck), 0.1f);
	this->schedule(schedule_selector(GameScene::Update));
	this->schedule(schedule_selector(GameScene::OneTwoThreeFourBubbleBubbleLeft));
	this->schedule(schedule_selector(GameScene::OneTwoThreeFourBubbleBubbleRight));
	this->schedule(schedule_selector(GameScene::GetCoinInTime),5.0f);
	return true;
}


void GameScene::Creat_Factory()
{
	//���丮 ����
	factory[FACTORY_RIGHT].Create(FACTORY_RIGHT);

	factory[FACTORY_LEFT].Create(FACTORY_LEFT);
	//���丮 ���
	this->addChild(factory[FACTORY_RIGHT].return_Menu());
	this->addChild(factory[FACTORY_RIGHT].return_HpBar_Back());
	this->addChild(factory[FACTORY_RIGHT].return_HpBar());
	this->addChild(factory[FACTORY_RIGHT].return_Factory_Sp());

	this->addChild(factory[FACTORY_LEFT].return_Menu());
	this->addChild(factory[FACTORY_LEFT].return_HpBar_Back());
	this->addChild(factory[FACTORY_LEFT].return_HpBar());
	this->addChild(factory[FACTORY_LEFT].return_Factory_Sp());
	//���� ���
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
	
	UI_Left_bottom_Unit = MenuItemImage::create("UI/UI_bottom_Unit.png", "UI/UI_bottom_Unit1.png", CC_CALLBACK_1(GameScene::ClickToCreateBubble1, this, 1, false));
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
	Lcoin->setPosition(Vec2(70, 73));
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

	//rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
	UI_Right_bottom_Info = Sprite::create("UI/UI_bottom_Info_Right.png");
	UI_Right_bottom_Info->setAnchorPoint(Vec2(1, 0));
	UI_Right_bottom_Info->setPosition(winSize.width, 0);
	this->addChild(UI_Right_bottom_Info);
	
	UI_Right_bottom_Bubble = MenuItemImage::create("UI/UI_bottom_Bubble.png", "UI/UI_bottom_Bubble1.png", CC_CALLBACK_1(GameScene::ClickToCreateBubble1, this, 1, true));
	UI_Right_bottom_Bubble->setAnchorPoint(Vec2(1, 0));
	UI_Right_bottom_Bubble->setPosition(winSize.width - UI_Right_bottom_Info->getContentSize().width, 0);

	UI_Right_bottom_Unit = MenuItemImage::create("UI/UI_bottom_Unit.png", "UI/UI_bottom_Unit1.png", CC_CALLBACK_1(GameScene::ClickToCreateBubble1, this, 1, false));
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
	Rcoin->setPosition(Vec2(winSize.width- 120, 73));
	Rcoin->setColor(Color3B::BLACK);
	this->addChild(Rcoin);

	auto menu2 = Menu::create(UI_Right_bottom_Bubble, UI_Right_bottom_Unit, nullptr);
	this->addChild(menu2);
	menu2->setPosition(Vec2::ZERO);

	Rbitcoincost = Label::createWithTTF("333", "fonts/Marker Felt.ttf", 24);
	Rbitcoincost->setString(StringUtils::format("%d", bubbleCostR));
	Rbitcoincost->setPosition(Vec2(winSize.width - 335, 20));
	Rbitcoincost->setColor(Color3B::BLACK);
	this->addChild(Rbitcoincost);

	//�κ�ĭ �ʱ�ȭ
	for (int i = 0; i < 4; i++)
	{
		invenPos_Left[i].x = UI_Left_bottom_Info->getContentSize().width + UI_Left_bottom_Bubble->getContentSize().width + 43 + i * 70;
		invenPos_Left[i + 4].x = UI_Left_bottom_Info->getContentSize().width + UI_Left_bottom_Bubble->getContentSize().width + 43 + i * 70;
		invenPos_Left[i].y = UI_Right_bottom_Bubble->getContentSize().height + 34;
		invenPos_Left[i + 4].y = UI_Right_bottom_Bubble->getContentSize().height - 34;

		invenPos_Right[3-i].x = winSize.width - (UI_Left_bottom_Info->getContentSize().width + UI_Left_bottom_Bubble->getContentSize().width + 43 + i * 70);
		invenPos_Right[3-i + 4].x = winSize.width - (UI_Left_bottom_Info->getContentSize().width + UI_Left_bottom_Bubble->getContentSize().width + 43 + i * 70);
		invenPos_Right[i].y = UI_Right_bottom_Bubble->getContentSize().height + 34;
		invenPos_Right[i + 4].y = UI_Right_bottom_Bubble->getContentSize().height - 34;
	}
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
	if (isRight)
	{
		if (bubblesRight.size() < 8 && (bitCoinR > bubbleCostR || lev==2))
		{
			bubblesRight.push_back(new Bubble);
			bubblesRight.back() = bubblesRight.back()->BubbleCreate(GetPP(lev));
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
			bubblesLeft.push_back(new Bubble);
			bubblesLeft.back() = bubblesLeft.back()->BubbleCreate(GetPP(lev));
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
#pragma region ������

void GameScene::Update(float f)
{
	if (GameManager::GetInstance()->Return_isRightFactory_Die)
	{
		//������ ���丮 ���
	}
	if (GameManager::GetInstance()->Return_isLeftFactory_Die)
	{
		//���� ���丮 ���
	}
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
		if (bubblesRight[i]->isMove())//�����̰� �ִٸ� �浹ó���� ���� �ʴ´�.
		{
			return;
		}
	}
	//�浹ö��//ù ���� �� ���ļ� �����Ǹ� �ٷ� ��������...
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
						invenPos_Right[bubblesRight[i]->GetPosNum()].isFull = false;
						bubblesRight[i]->removeFromParentAndCleanup(true);
						bubblesRight.erase(bubblesRight.begin() + i);
						if (i != j)
						{
							invenPos_Right[bubblesRight[j - 1]->GetPosNum()].isFull = false;
							bubblesRight[j - 1]->removeFromParentAndCleanup(true);
							bubblesRight.erase(bubblesRight.begin() + j - 1);
						}
						//new ���� ���� �ڵ�
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
			invenPos_Right[bubblesRight[i]->GetPosNum()].isFull = false;
			bubblesRight[i]->removeFromParentAndCleanup(true);
			bubblesRight.erase(bubblesRight.begin() + i);
			break;
		}

		if (bubblesRight[i]->getBoundingBox().intersectsRect(UI_Right_bottom_Delet->getBoundingBox()))
		{
			bitCoinR += bubbleCostR * 0.5f - 10;
			Rcoin->setString(StringUtils::format("%d", bitCoinR));
			invenPos_Right[bubblesRight[i]->GetPosNum()].isFull = false;
			bubblesRight[i]->removeFromParentAndCleanup(true);
			bubblesRight.erase(bubblesRight.begin() + i);
		}
		else
		{
			bubblesRight[i]->setPosition(Vec2(invenPos_Right[bubblesRight[i]->GetPosNum()].x, invenPos_Right[bubblesRight[i]->GetPosNum()].y));
		}
	}
}
void GameScene::OneTwoThreeFourBubbleBubbleLeft(float f)
{
	for (int i = 0; i < bubblesLeft.size(); i++)
	{
		if (bubblesLeft[i]->isMove())//�����̰� �ִٸ� �浹ó���� ���� �ʴ´�.
		{
			return;
		}
	}
	//�浹ö��//ù ���� �� ���ļ� �����Ǹ� �ٷ� ��������...
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
						invenPos_Left[bubblesLeft[i]->GetPosNum()].isFull = false;
						bubblesLeft[i]->removeFromParentAndCleanup(true);
						bubblesLeft.erase(bubblesLeft.begin() + i);
						if (i != j)
						{
							invenPos_Left[bubblesLeft[j - 1]->GetPosNum()].isFull = false;
							bubblesLeft[j - 1]->removeFromParentAndCleanup(true);
							bubblesLeft.erase(bubblesLeft.begin() + j - 1);
						}
						//new ���� ���� �ڵ�
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
		if (bubblesLeft[i]->getBoundingBox().intersectsRect(factory[FACTORY_LEFT].return_Factory_Sp()->getBoundingBox()))
		{
			factory[FACTORY_LEFT].Change_Bubble(bubblesLeft[i]->BubbleStat_rt());
			invenPos_Left[bubblesLeft[i]->GetPosNum()].isFull = false;
			bubblesLeft[i]->removeFromParentAndCleanup(true);
			bubblesLeft.erase(bubblesLeft.begin() + i);
			break;
		}
	
		if (bubblesLeft[i]->getBoundingBox().intersectsRect(UI_Left_bottom_Delet->getBoundingBox()))
		{
			bitCoinL += bubbleCostL * 0.5f - 10;
			Lcoin->setString(StringUtils::format("%d", bitCoinL));
			invenPos_Left[bubblesLeft[i]->GetPosNum()].isFull = false;
			bubblesLeft[i]->removeFromParentAndCleanup(true);
			bubblesLeft.erase(bubblesLeft.begin() + i);
		}
		else
		{
			bubblesLeft[i]->setPosition(Vec2(invenPos_Left[bubblesLeft[i]->GetPosNum()].x, invenPos_Left[bubblesLeft[i]->GetPosNum()].y));
		}
	}
}
#pragma endregion

