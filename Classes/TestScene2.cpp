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
	auto m_3 = MenuItemImage::create("btn-play-normal.png", "btn-play-selected.png", CC_CALLBACK_1(TestScene2::ClickToCreateBubble1, this));
	auto m_4 = MenuItemImage::create("end1.PNG", "end2.PNG", CC_CALLBACK_1(TestScene2::ClickToCreateBubble1, this));
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
	randnum = rand() % 6;

	val.Hp = 0;
	val.Defense = 0;
	val.Damage = 0;
	val.AttackSpeed = 0;
	val.MoveSpeed = 0;
	val.Spawn_time = 0;
	val.level = lev;

	if (val.level ==1)
	{
		switch (randnum)
		{
		case 0:
			val.Damage = 5;
			break;
		case 1:
			val.Defense = 5;
			break;
		case 2:
			val.Spawn_time = -0.1f;
			break;
		case 3:
			val.MoveSpeed = 2;
			break;
		case 4:
			val.AttackSpeed = 0.5f;
			break;
		case 5:
			val.Hp = 5;
			break;
		default:
			break;
		}
	}
	else if(val.level ==2)
	{
		switch (randnum)
		{
		case 0:
			val.Damage = 10;
			break;
		case 1:
			val.Defense = 10;
			break;
		case 2:
			val.Spawn_time = -0.3f;
			break;
		case 3:
			val.MoveSpeed = 3;
			break;
		case 4:
			val.AttackSpeed = 1;
			break;
		case 5:
			val.Hp = 15;
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

void TestScene2::ClickToCreateBubble1(Ref* pSender)
{
	//bubbles.push_back(new Bubble);
	//bubbles.back()->BubbleCreate(GetPP(1));
	//bubbles.back()->setPr(10);
	//bubbles.back()->setPrWiththis(false);
	//this->addChild(bubbles.back()->Bubble_rt());

	bubbles.push_back(new Bubble);
	bubbles.back()=bubbles.back()->BubbleCreate(GetPP(1));// = Bubble::create("white-512x512.png");

	this->addChild(bubbles.back());
	//bubbleB = Bubble::create("white-512x512.png");
	//bubbleB->setScale(0.2, 0.2); 
	//bubbleB->setColor(Color3B(127 - count, 100, 255));
	//bubbleB->setPosition(Vec2(100 + count, 160));
	//bubbleB->setPr(10);
	//bubbleB->setPrWiththis(false);
	//this->addChild(bubbleB);

}

void TestScene2::Click2(Ref* pSender)
{
	log("run callback");
	auto m = (Bubble*)pSender;
	this->removeChild(m, true);
}

void TestScene2::myTick(float f)
{
	//간단한 충돌체크
	//if (bubbleA != nullptr&& bubbleB != nullptr)
	//{
	//	if ((bubbleA->isMove() || bubbleB->isMove()) && bubbleA->getBoundingBox().intersectsRect(bubbleB->getBoundingBox()))
	//	{
	//		log("C Check");
	//		bubbleA->removeFromParentAndCleanup(true);
	//		bubbleA = nullptr;
	//		bubbleB->removeFromParentAndCleanup(true);
	//		bubbleB = nullptr;
	//		CreateBubble2();
	//	}
	//}
}