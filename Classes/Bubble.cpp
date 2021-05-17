#include "Bubble.h"

USING_NS_CC;

Bubble* Bubble::create(const std::string& filename)
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
		this->setPosition(this->getPosition() + touch->getDelta());//�̵�������
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		_isMove = false;
		log("touch end...");
		//this->setColor(Color3B::WHITE);
	};

	if (_useNodePr)
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this); //�׷��� ����
	else
		_eventDispatcher->addEventListenerWithFixedPriority(listener, _fixedPr); // ������ �켱�������

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