#pragma once
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#endif

#include "cocos2d.h"

using namespace cocos2d;

class TestScene1;

class Unit : public cocos2d::Sprite
{
public:
	//스테이터스
	float maxHp; //최대 체력
	float hp; //현재 체력
	float speed; //이동속도
	float power; //힘

	bool isFighting = false; //싸우는 중인지
	bool isDied = false; //죽었는지
	
	
	//팩토리 정보
	Vec2 myFactory;
	Vec2 enemyFactory;

	//HP바
	Sprite* emptyHP;
	Sprite* fullHP;


	//함수
	void initUnit(); //유닛 초기화
	void initUnitL(); //유닛 초기화
	void initUnitR(); //유닛 초기화

	void virtual moveUnit() = 0; //유닛 이동
	void virtual attackUnit(Unit* enemy) = 0; //적 유닛 공격하기
	void damaged(float damage); //데미지를 입는 함수
	void virtual dieUnit() = 0; //유닛 사망

	//콜백 함수
	void virtual callbackAttack(Unit* enemy) { }

	//스케줄 함수
	void virtual update(float f) = 0;
};

class LeftUnit :public Unit
{
public:
	static Unit* createUnitL(); //유닛 생성

	void moveUnit() override; //유닛 이동
	void attackUnit(Unit* enemy) override; //적유닛 공격하기
	void dieUnit() override; //유닛 사망
	void update(float f) override;

	//콜백 함수
	void callbackAttack(Unit* enemy) override; //attackUnit에서 호출하는 함수
};

class RightUnit :public Unit
{
public:
	static Unit* createUnitR(); //유닛 생성

	//스케줄 함수
	void moveUnit() override; //유닛 이동
	void attackUnit(Unit* enemy) override; //적유닛 공격하기
	void dieUnit() override; //유닛 사망
	void update(float f) override;

	//콜백 함수
	void callbackAttack(Unit* enemy) override; //attackUnit에서 호출하는 함수
};