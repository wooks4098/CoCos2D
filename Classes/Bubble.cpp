#include "Bubble.h"
#include "SoundManager.h"
USING_NS_CC;

Bubble* Bubble::create(const std::string& filename)//, BUBBLE b_slot)
{
	Bubble* sprite = new(std::nothrow)Bubble(); // nothrow > ���� �߸� �����ɶ� ���α׷� �����ʵ���
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Bubble* Bubble::create()
{
	Bubble* sprite = new(std::nothrow)Bubble(); // nothrow > ���� �߸� �����ɶ� ���α׷� �����ʵ���
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Bubble* Bubble::BubbleCreate(BUBBLE info)
{
	b_stat = info;
	switch (b_stat.key)
	{
	case 0:
		pBub = Bubble::create("Bubble/new_60/C1_Blue.png");
		break;
	case 1:
		pBub = Bubble::create("Bubble/new_60/C1_Red.png");
		break;
	case 2:
		pBub = Bubble::create("Bubble/new_60/C1_Yellow.png");
		break;
	case 3:
		pBub = Bubble::create("Bubble/new_60/C2_Blue.png");
		break;
	case 4:
		pBub = Bubble::create("Bubble/new_60/C2_Red.png");
		break;
	case 5:
		pBub = Bubble::create("Bubble/new_60/C2_Yellow.png");
		break;
	case 6:
		pBub = Bubble::create("Bubble/new_60/R1_Blue.png");
		break;
	case 7:
		pBub = Bubble::create("Bubble/new_60/R1_Red.png");
		break;
	case 8:
		pBub = Bubble::create("Bubble/new_60/R1_Yellow.png");
		break;
	case 9:
		pBub = Bubble::create("Bubble/new_60/R2_Blue.png");
		break;
	case 10:
		pBub = Bubble::create("Bubble/new_60/R2_Red.png");
		break;
	case 11:
		pBub = Bubble::create("Bubble/new_60/R2_Yellow.png");
		break;

	default:
		break;
	}
	

	pBub->b_stat = b_stat;
	//pBub->setPosition(Vec2(100, 100));
	pBub->setPr(10);
	pBub->setPrWiththis(true);
	return pBub;
}


bool Bubble::isMove()
{
	return _isMove;
}
void Bubble::onEnter()
{
	log("on Bubble...");

	Sprite::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{


		log("touch dd...");
		Vec2 basepoint = touch->getLocation();
	
		Vec2 LocationInNode = this->convertToNodeSpace(touch->getLocation());
	
		Size s = this->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(LocationInNode))
		{
			SoundManager::GetInstance()->Play(Bubble_Select);
			_isMove = true;
			log("touch Bubble...");
			return true;
		}
		return false; //�߰��Ѱ�
	};
	
	listener->onTouchMoved = [=](Touch* touch, Event* event)
	{
		//log("touch mv...", _isMove);
		this->setPosition(this->getPosition() + touch->getDelta());//�̵�������
	};
	
	listener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		_isMove = false;
		//log("touch end...");
	};
	
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this); //�׷��� ����
	//if (_useNodePr)
	//else
	//	_eventDispatcher->addEventListenerWithFixedPriority(listener, _fixedPr); // ������ �켱�������
	//
	_listener = listener; //ȭ�� ���� �� ��ġ�ϸ� ������ ����� ȭ�� ������� ������ ����
}

void Bubble::onExit()
{
	_eventDispatcher->removeEventListener(_listener);
	Sprite::onExit();
}

void Bubble::setPr(int fixedPr)
{
	_fixedPr = fixedPr;
}

void Bubble::setPrWiththis(bool useNodePr)
{
	_useNodePr = useNodePr;
}
