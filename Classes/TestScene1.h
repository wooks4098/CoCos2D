#pragma
#include "Unit.h"

class TestScene1 : public cocos2d::Scene
{
private:
	TestScene1();
	~TestScene1() {};
	static TestScene1* instance;

public:
	static cocos2d::Scene* createScene();
	static TestScene1* getInstance();
	static void releaseInstance();

	virtual bool init();

	Size winSize = Director::getInstance()->getWinSize();

	//���丮 ����
	Vec2 facL = Vec2(0, winSize.height / 2);
	Vec2 facR = Vec2(winSize.width, winSize.height / 2);

	Unit* remove = nullptr;

	//Vector<Unit*> getVector(Vec2 fac);

	//������ �ʱ�ȭ
	void initData();

	//���� �浹
	void update(float f) override;

	//���� ����
	void callbackRemove(Unit* unit);

	//������ �Լ�
	void addUnitL(float f);
	void addUnitR(float f);


	CREATE_FUNC(TestScene1);
};