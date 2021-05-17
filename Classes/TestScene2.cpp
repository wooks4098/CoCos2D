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

    auto wlayer = LayerColor::create(Color4B(100,255,255,100));
    this->addChild(wlayer);


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

	this->schedule(schedule_selector(TestScene2::myTick));

    return true;
}

void TestScene2::ClickToCreateBubble1(Ref* pSender)
{
	count = rand() % 25+ 100;


	if (count % 2 == 1)
	{
		bubbleA = Bubble::create("white-512x512.png");
		bubbleA->setScale(0.2, 0.2);
		bubbleA->setColor(Color3B(127 + count, 100, 255));
		bubbleA->setPosition(Vec2(100 , 160+ count));
		bubbleA->setPr(10);
		bubbleA->setPrWiththis(false);
		this->addChild(bubbleA);
	}
	else
	{
		bubbleB = Bubble::create("white-512x512.png");
		bubbleB->setScale(0.2, 0.2); 
		bubbleB->setColor(Color3B(127 - count, 100, 255));
		bubbleB->setPosition(Vec2(100 + count, 160));
		bubbleB->setPr(10);
		bubbleB->setPrWiththis(false);
		this->addChild(bubbleB);
	}

}

void TestScene2::Click2(Ref* pSender)
{
	log("run callback");
	auto m = (Bubble*)pSender;
	this->removeChild(m, true);
}

void TestScene2::CreateBubble2()
{
	bubbleC = Bubble::create("white-512x512.png");
	bubbleC->setScale(0.2, 0.2);
	bubbleC->setColor(Color3B(100, 100, 100));
	bubbleC->setPosition(Vec2(200+count, 160));
	bubbleC->setPr(10);
	bubbleC->setPrWiththis(false);
	this->addChild(bubbleC);
}

void TestScene2::myTick(float f)
{
	//간단한 충돌체크
	if (bubbleA != nullptr&& bubbleB != nullptr)
	{
		if ((bubbleA->isMove() || bubbleB->isMove()) && bubbleA->getBoundingBox().intersectsRect(bubbleB->getBoundingBox()))
		{
			log("C Check");
			bubbleA->removeFromParentAndCleanup(true);
			bubbleA = nullptr;
			bubbleB->removeFromParentAndCleanup(true);
			bubbleB = nullptr;
			CreateBubble2();
		}
	}
}