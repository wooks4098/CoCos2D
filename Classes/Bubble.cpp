#include "Bubble.h"

USING_NS_CC;

Bubble* Bubble::create(const std::string& filename)//, BUBBLE b_slot)
{
	Bubble* sprite = new(std::nothrow)Bubble(); // nothrow > 몬스터 잘못 생성될때 프로그래 죽지않도록
	if (sprite && sprite->initWithFile(filename))
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
	pBub = new(std::nothrow)Bubble();

	if (b_stat.Defense != 0)
	{
		b_stat.Defense += 5;
		if (b_stat.level == 1)
			pBub = Bubble::create("Bubble/C1_Blue.png");
		else if (b_stat.level == 2)
			pBub = Bubble::create("Bubble/C2_Blue.png");
		b_stat.iscircle = true;
		log(b_stat.Defense);
	}
	if (b_stat.Hp != 0)
	{
		b_stat.Hp += 100;
		if (b_stat.level == 1)
			pBub = Bubble::create("Bubble/C1_Red.png");
		else if (b_stat.level == 2)
			pBub = Bubble::create("Bubble/C2_Red.png");
		b_stat.iscircle = true;
		log(b_stat.Hp);
	}
	if (b_stat.Spawn_time != 0)
	{
		b_stat.Spawn_time += 3;
		if (b_stat.level == 1)
			pBub = Bubble::create("Bubble/C1_Yellow.png");
		else if (b_stat.level == 2)
			pBub = Bubble::create("Bubble/C2_Yellow.png");
		b_stat.iscircle = true;
		log(b_stat.Spawn_time);
	}
	if (b_stat.Damage != 0)
	{
		b_stat.Damage += 10;
		if (b_stat.level == 1)
			pBub = Bubble::create("Bubble/R1_Blue.png");
		else if (b_stat.level == 2)
			pBub = Bubble::create("Bubble/R2_Blue.png");
		b_stat.iscircle = false;
		log(b_stat.Damage);
	}
	if (b_stat.AttackSpeed != 0)
	{
		b_stat.AttackSpeed += 1;
		if (b_stat.level == 1)
			pBub = Bubble::create("Bubble/R1_Red.png");
		else if (b_stat.level == 2)
			pBub = Bubble::create("Bubble/R2_Red.png");
		b_stat.iscircle = false;
		log(b_stat.AttackSpeed);
	}
	if (b_stat.MoveSpeed != 0)
	{
		b_stat.MoveSpeed += 5;
		if (b_stat.level == 1)
			pBub = Bubble::create("Bubble/R1_Yellow.png");
		else if(b_stat.level == 2)
			pBub = Bubble::create("Bubble/R2_Yellow.png");
		b_stat.iscircle = false;
		log(b_stat.MoveSpeed);
	}
	
	pBub->setPosition(Vec2(300, 200));
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
	Sprite::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		log("touch bg...");
		Vec2 basepoint = touch->getLocation();

		Vec2 LocationInNode = this->convertToNodeSpace(touch->getLocation());

		Size s = this->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(LocationInNode))
		{
			return true;
		}
	};

	listener->onTouchMoved = [=](Touch* touch, Event* event)
	{
		_isMove = true;
		log("touch mv...", _isMove);
		this->setPosition(this->getPosition() + touch->getDelta());//이동한정보
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		_isMove = false;
		log("touch end...");
	};

	if (_useNodePr)
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this); //그려진 순서
	else
		_eventDispatcher->addEventListenerWithFixedPriority(listener, _fixedPr); // 지정된 우선순위대로

	_listener = listener; //화면 보일 때 터치하면 리스너 만들고 화면 사라지면 리스너 제거
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