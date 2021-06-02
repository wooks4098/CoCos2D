#pragma once
#include <Unit.h>

class RightUnit :public Unit
{
public:
	static Unit* createUnit(Factory* myFac, Factory* enemyFac); //유닛 생성

	void initUnit() override; //유닛 초기화

	void idleUnit() override; //유닛 대기
	void moveUnit() override; //유닛 이동
	void attackUnit(Unit* enemy) override; //적유닛 공격하기
	void dieUnit() override; //유닛 사망
	void update(float f) override;

	//콜백 함수
	void callbackAttack(Unit* enemy) override; //attackUnit에서 호출하는 함수
};