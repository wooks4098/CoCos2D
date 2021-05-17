#include "Bubble.h"

USING_NS_CC;

Bubble* Bubble::create(const std::string& filename)
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
			//this->setColor(Color3B::RED);
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
		//this->setColor(Color3B::WHITE);
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