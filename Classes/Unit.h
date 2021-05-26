#pragma once
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#endif

#include "cocos2d.h"
using namespace cocos2d;

class TestScene1;

class Unit : public cocos2d::Sprite
{
private:
	//스테이터스
	float maxHp;
	float hp;
	float speed;
	float power;
	
	//팩토리 정보
	Vec2 myFactory;
	Vec2 enemyFactory;

public:
	static Unit* createUnit(Vec2 v); //유닛 생성
	void initUnit(); //유닛 초기화
	void unitAni(); //유닛 애니메이션
	
	void moveUnit(float speed); //유닛 이동
	void stopUnit(); //유닛 이동 정지
	void hit(float f); //적유닛을 공격하는 함수
	void damaged(); //적유닛에게 공격 받는 함수
	void die(); //유닛 사망

	//get
	float getHp() { return hp; }
	Vec2 getMyFac() { return myFactory; }

	//공격할 대상
	Unit* enemy;

	//애니메이션
	MoveTo* move;

	Animation* moveAni;
	Animation* attackAni;
	Animation* dieAni;

	Animate* moveAct;
	Animate* attackAct;
	Animate* dieAct;

	RepeatForever* rep;

	//스케줄 함수
	void actionMove(float f);
	void actionAttack(float f);
	void actionDie(float f);
	
	void update(float f) override;

	//HP바
	Sprite* emptyHP;
	Sprite* fullHP;
};