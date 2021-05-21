#include "TestScene2.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

Scene* TestScene2::createScene()
{
    return TestScene2::create();
}

bool TestScene2::init()
{
    if (!Scene::init())
    {
        return false;
    }
	srand(time(NULL));



    auto wlayer = LayerColor::create(Color4B(100,255,255,100));
    this->addChild(wlayer);

	#pragma region menu
	auto m_3 = MenuItemImage::create("btn-play-normal.png", "btn-play-selected.png", CC_CALLBACK_1(TestScene2::ClickToCreateBubble1, this,1));
	auto m_4 = MenuItemImage::create("end1.PNG", "end2.PNG", CC_CALLBACK_1(TestScene2::ClickToCreateBubble1, this,1));
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

	this->schedule(schedule_selector(TestScene2::myTick));

    return true;
}
BUBBLE TestScene2::GetPP(int lev)
{

	val.Hp = 0;
	val.Defense = 0;
	val.Damage = 0;
	val.AttackSpeed = 0;
	val.MoveSpeed = 0;
	val.SpawnSpeed = 0;
	

	if (lev==1)
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
	else if(lev==2)
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

void TestScene2::ClickToCreateBubble1(Ref* pSender,int lev)
{
	//bubbles.push_back(new Bubble);
	//bubbles.back()->BubbleCreate(GetPP(1));
	//bubbles.back()->setPr(10);
	//bubbles.back()->setPrWiththis(false);
	//this->addChild(bubbles.back()->Bubble_rt());

	bubbles.push_back(new Bubble);
	bubbles.back()=bubbles.back()->BubbleCreate(GetPP(lev));

	this->addChild(bubbles.back());
}

void TestScene2::Click2(Ref* pSender)
{
	log("run callback");
	auto m = (Bubble*)pSender;
	this->removeChild(m, true);
}

void TestScene2::myTick(float f)
{
	for (int i = 0; i < bubbles.size(); i++)
	{
		if (bubbles[i]->isMove())//움직이고 있다면 충돌처리를 하지 않는다.
		{
			return;
		}
	}
	//충돌철이//첫 생성 시 겹쳐서 생성되면 바로 합쳐진다...
	if(bubbles.size()>=2)
	{
		for (int i = 0; i < bubbles.size(); i++)
		{
			for (int j = i+1; j < bubbles.size(); j++)
			{
				if (bubbles[i]->getBoundingBox().intersectsRect(bubbles[j]->getBoundingBox()))
				{
					if (bubbles[i]->BubbleStat_rt().key <= 5 && bubbles[i]->BubbleStat_rt().key == bubbles[j]->BubbleStat_rt().key)
					{
						log("C Check");
						bubbles[i]->removeFromParentAndCleanup(true);
						bubbles.erase(bubbles.begin() + i);
						if (i!=j)
						{
							bubbles[j-1]->removeFromParentAndCleanup(true);
							bubbles.erase(bubbles.begin() + j - 1);
						}
						//new 버블 생성 코드
						ClickToCreateBubble1(this, 2);
						return;
					}
				}
			}
		}
	}
}