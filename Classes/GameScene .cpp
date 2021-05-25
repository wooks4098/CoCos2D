
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

	Create_BackGround();
	Creat_Factory();

	//������ ���
	this->schedule(schedule_selector(GameScene::Factory_Right_CreatUnitCheck), 0.1f);
	this->schedule(schedule_selector(GameScene::Factory_Left_CreatUnitCheck), 0.1f);
	this->schedule(schedule_selector(GameScene::Update));
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
	for (int i = 0; i < 7; i++)
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
			val.Damage = 10;
			val.key = 6;
			break;
		case C2_Red:
			val.Defense = 10;
			val.key = 7;
			break;
		case C2_Yellow:
			val.SpawnSpeed = -0.3f;
			val.key = 8;
			break;
		case R2_Blue:
			val.MoveSpeed = 3;
			val.key = 9;
			break;
		case R2_Red:
			val.AttackSpeed = 1;
			val.key = 10;
			break;
		case R2_Yellow:
			val.Hp = 15;
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
#pragma region ������

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
void GameScene::OneTwoThreeFourBubbleBubble(float f)
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
						log("C Check");
						bubblesLeft[i]->removeFromParentAndCleanup(true);
						bubblesLeft.erase(bubblesLeft.begin() + i);
						if (i != j)
						{
							bubblesLeft[j - 1]->removeFromParentAndCleanup(true);
							bubblesLeft.erase(bubblesLeft.begin() + j - 1);
						}
						//new ���� ���� �ڵ�
						ClickToCreateBubble1(this, 2, true);
						return;
					}
				}
				//else if (bubbles[i]->getBoundingBox().intersectsRect())
				{

				}
			}
		}
	}
}
#pragma endregion

