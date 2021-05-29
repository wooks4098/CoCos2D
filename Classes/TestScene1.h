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

	//팩토리 정보
	Vec2 facL = Vec2(0, winSize.height / 2);
	Vec2 facR = Vec2(winSize.width, winSize.height / 2);

	//모든 유닛 저장
	Vector<Unit*> unitsL;
	Vector<Unit*> unitsR;

	//데이터 초기화
	void initData();

	//유닛 생성
	void createUnitL();
	void createUnitR();

	//유닛 충돌
	void update(float f) override;

	//유닛 제거
	void removeUnit(Ref* pSender);

	//스케줄 함수
	void addUnitL(float f); //유닛 추가
	void addUnitR(float f); //유닛 추가


	CREATE_FUNC(TestScene1);
};