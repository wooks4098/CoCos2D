#pragma
#include "Unit.h"

class TestScene1 : public cocos2d::Scene
{
private:
	TestScene1() {};
	static TestScene1* instance;

public:
	static cocos2d::Scene* createScene();
	static TestScene1* getInstance();

	virtual bool init();

	Size winSize = Director::getInstance()->getWinSize();

	//���丮 ����
	Vec2 facL = Vec2(0, winSize.height / 2);
	Vec2 facR = Vec2(winSize.width, winSize.height / 2);

	//��� ���� ����
	Vector<Unit*> unitsL;
	Vector<Unit*> unitsR;

	//������ �ʱ�ȭ
	void initData();

	//���� ����
	void createUnit(Vec2 v);

	//���� �浹
	void update(float f) override;

	//���� ����
	void removeUnit(Unit* u);

	CREATE_FUNC(TestScene1);
};