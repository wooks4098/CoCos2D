#pragma once
#include <Unit.h>

class RightUnit :public Unit
{
public:
	static Unit* createUnit(Factory* myFac, Factory* enemyFac, BUBBLE bubble); //유닛 생성
	void initUnit(BUBBLE bubble) override; //유닛 초기화

	void idleUnit() override; //유닛 대기
	void moveUnit() override; //유닛 이동
	void attackUnit(Unit* enemy) override; //적 유닛 공격
	void attackFactory() override; //적 팩토리 공격
	void damaged(float damage) override; //데미지 입는 함수
	void dieUnit() override; //유닛 사망
	void removeUnit() override; //유닛 제거
	void removeVector() override; //벡터에 있는 유닛 제거

	void callbackAttack(Unit* enemy) override; //attackUnit에서 호출
	void callbackAttackFac() override; //attackFactory에서 호출

	//스케줄 함수
	void update(float f) override; //유닛 충돌 체크
};